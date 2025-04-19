#include "..\framework.h"

#include "../Public/Driver.h"

FNetworkObjectList& Driver::GetNetworkObjectList(UNetDriver* Driver)
{
	return *(*(TSharedPtr<FNetworkObjectList>*)(__int64(Driver) + 0x490));
}

// this could be the function but hahahah.......
AActor* Driver::GetArcheType(AActor* Actor) {
	// most 1:1 function
	static __int64 (*sub_7FF76659AD50)(UClass * a1, UObject * a2, FName a3, EObjectFlags a4) = decltype(sub_7FF76659AD50)(ImageBase + 0xDFAD50);
	//sub_7FF76659AD50(_QWORD *a1, __int64 a2, __int64 a3, int a4) wow man 
	if (Actor->BlueprintCreatedComponents.IsValid()) {
		//std::cout << "BlueprintCreatedComponents ISNT EMPTY " << std::endl;
		return (AActor*)sub_7FF76659AD50(
			Actor->BlueprintCreatedComponents[0]->Class,
			Actor->BlueprintCreatedComponents[0]->Outer,
			Actor->BlueprintCreatedComponents[0]->Name,
			Actor->BlueprintCreatedComponents[0]->Flags
		);
	}
	else {

		return nullptr;
	}
}

int32 Driver::ServerReplicateActors_PrepConnections(UNetDriver* NetDriver, float a2) {

	int32 NumClientsToTick = NetDriver->ClientConnections.Num();
	bool bFoundReadyConnection = false;

	/*	static float DeltaTimeOverflow = 0.f;
		float ClientUpdatesThisFrame = UEngine::GetEngine()->NetClientTicksPerSecond * (a2 + DeltaTimeOverflow) * (1.f);
		NumClientsToTick = UKismetMathLibrary::Min(NumClientsToTick, UKismetMathLibrary::FTrunc(ClientUpdatesThisFrame));
		if (NumClientsToTick == 0) {
			DeltaTimeOverflow += a2;
			return 0;
		}
		DeltaTimeOverflow = 0.f;*/

	if (NetDriver->ClientConnections.Num() > 0) {
		for (int i = 0; i < NetDriver->ClientConnections.Num(); i++) {
			UNetConnection* Connection = NetDriver->ClientConnections[i];
			if (!Connection) {
				continue;
			}
			AActor* OwningActor = Connection->OwningActor;
			if (OwningActor != NULL && (NetDriver->Time - Connection->LastReceiveTime < 1.5f)) {

				bFoundReadyConnection = true;

				Connection->ViewTarget = Connection->PlayerController ? Connection->PlayerController->GetViewTarget() : OwningActor;

				for (int32 Childi = 0; i < Connection->Children.Num(); Childi++) {
					UNetConnection* child = Connection->Children[Childi];
					auto PC = child->PlayerController;
					if (PC) {
						child->ViewTarget = PC->GetViewTarget();
					}
					else {
						child->ViewTarget = NULL;
					}
				}
			}
			else
			{
				Connection->ViewTarget = NULL;
				for (int32 f = 0; f < Connection->Children.Num(); f++) {
					Connection->Children[f]->ViewTarget = NULL;
				}
			}
		}
	}
	return bFoundReadyConnection ? NumClientsToTick : 0;
}

std::vector<FNetworkObjectInfo*> Driver::ServerReplicateActors_BuildConsiderList(UNetDriver* Driver, float a2) {
	int32 NumInitallyDormant = 0;

	std::vector<FNetworkObjectInfo*> Actors;

	TArray<AActor*> ActorsToRemove;
	static bool IsThisProperEnough = false;
	for (const TSharedPtr<FNetworkObjectInfo>& ObjectInfo : GetNetworkObjectList(Driver).AllNetworkObjects) {
		FNetworkObjectInfo* ActorInfo = ObjectInfo.Get();

		if (!IsThisProperEnough) {
			if (ActorInfo->Actor->IsA(ABuildingContainer::StaticClass())) {
				ABuildingContainer* Actor = (ABuildingContainer*)ActorInfo->Actor;

				if (Actor && Actor->Class) {
					std::string ClassName = Actor->Class->GetName();
					if (!ClassName.contains("Tiered_Short_Ammo") && !ClassName.contains("Tiered_Chest")) {
						Actor->bAlreadySearched = true;
						Actor->OnRep_bAlreadySearched();
					}
				}
			}

		}
		if (!ActorInfo->bPendingNetUpdate && UGameplayStatics::GetTimeSeconds(UWorld::GetWorld()) <= ActorInfo->NextUpdateTime) {
			continue;
		}

		AActor* Actor = ActorInfo->Actor;

		if (!Actor) continue;

		if (Actor->bActorIsBeingDestroyed) {
			ActorsToRemove.Add(Actor);
			continue;
		}

		if (Actor->RemoteRole == ENetRole::ROLE_None) {
			ActorsToRemove.Add(Actor);
			continue;
		}

		if (Actor->NetDriverName != Driver->NetDriverName) {
			std::cout << Actor->GetName() << std::endl;
			continue;
		}

		ULevel* Level = (ULevel*)Actor->Outer;

		if (Actor && Actor->bNetStartup && Actor->NetDormancy == ENetDormancy::DORM_Initial) {
			NumInitallyDormant++;
			ActorsToRemove.Add(Actor);
			continue;
		}

		if (ActorInfo->LastNetReplicateTime == 0) {
			ActorInfo->LastNetReplicateTime = UGameplayStatics::GetTimeSeconds(UWorld::GetWorld());
			ActorInfo->OptimalNetUpdateDelta = 1.0f / Actor->NetUpdateFrequency;
		}

		const float ScaleDownStartTime = 2.0f;
		const float ScaleDownTimeRange = 5.0f;

		const float LastReplicateDelta = UGameplayStatics::GetTimeSeconds(UWorld::GetWorld()) - ActorInfo->LastNetReplicateTime;

		if (LastReplicateDelta > ScaleDownStartTime) {
			if (Actor->MinNetUpdateFrequency == 0.0f)
				Actor->MinNetUpdateFrequency = 2.0f;

			const float MinOptimalDelta = 1.0f / Actor->NetUpdateFrequency;
			const float MaxOptimalDelta = UKismetMathLibrary::FMax(1.0f / Actor->MinNetUpdateFrequency, MinOptimalDelta);

			const float Alpha = UKismetMathLibrary::FClamp((LastReplicateDelta - ScaleDownStartTime) / ScaleDownTimeRange, 0.0f, 1.0f);
			ActorInfo->OptimalNetUpdateDelta = UKismetMathLibrary::Lerp(MinOptimalDelta, MaxOptimalDelta, Alpha);
		}

		if (!ActorInfo->bPendingNetUpdate) {
			const float NextUpdateDelta = ActorInfo->OptimalNetUpdateDelta;

			//float RandomDelay = UGameplayStatics::GetTimeSeconds(UWorld::GetWorld()) + UKismetMathLibrary::RandomFloat();
			ActorInfo->NextUpdateTime = UGameplayStatics::GetTimeSeconds(UWorld::GetWorld()) + UKismetMathLibrary::RandomFloat() * a2 + NextUpdateDelta;
			ActorInfo->LastNetUpdateTime = Driver->Time;
		}

		ActorInfo->bPendingNetUpdate = false;

		Actors.push_back(ActorInfo);

		CallPreReplication(Actor, Driver);
	}
	// should only happen once
	IsThisProperEnough = true;

	for (AActor* Actor : ActorsToRemove) {
		if (!Actor) continue;
		//GetNetworkObjectList(Driver).Remove(Actor); // stop being lazy!
		//static bool (*removeac)(AActor* Actor) = decltype(removeac)(ImageBase + 0x1AEBB40);
		//removeac(Actor);
		GetNetworkObjectList(Driver).Remove2(Actor);
		//7FF766402F80 ~ 0xC62F80
	}

	return Actors;
}

UActorChannel* Driver::FindActorChannel(UNetConnection* Connection, AActor* Actor) {
	for (UChannel* Channel : Connection->OpenChannels) {
		if (Channel->Class == UActorChannel::StaticClass()) {
			if (((UActorChannel*)Channel)->Actor == Actor) return (UActorChannel*)Channel;
		}
	}

	return nullptr;
}

AActor* Driver::GetNetOwner(AActor* Actor) {
	if (Actor) {
		if (Actor->IsA(APlayerController::StaticClass()))
			if (((APlayerController*)Actor)->NetConnection)
				return Actor;

		if (Actor->IsA(APawn::StaticClass()))
			return Actor;

		return Actor->Owner;
	}
	return nullptr; // null
}

UNetConnection* Driver::IsActorOwnedByAndRelevantToConnection(AActor* Actor, const TArray<FNetViewer>& ConnectionViewers, bool& bOutHasNullViewTarget)
{
	AActor* ActorOwner = GetNetOwner(Actor);
	bOutHasNullViewTarget = false;

	for (int i = 0; i < ConnectionViewers.Num(); i++)
	{
		UNetConnection* ViewerConnection = ConnectionViewers[i].Connection;
		if (!ViewerConnection) continue;

		if (ViewerConnection->ViewTarget == nullptr)
			bOutHasNullViewTarget = true;

		if (ActorOwner == ViewerConnection->PlayerController ||
			(ViewerConnection->PlayerController && ActorOwner == ViewerConnection->PlayerController->Pawn) ||
			(ViewerConnection->ViewTarget && ViewerConnection->ViewTarget->IsRelevancyOwnerFor(Actor, ActorOwner, ViewerConnection->OwningActor) //ActorOwner
				))
		{
			return ViewerConnection;
		}
	}

	return nullptr;
}

bool Driver::IsActorRelevantToConnection(AActor* Actor, TArray<FNetViewer>& ConnectionViewers) {
	for (int32 viewerIdx = 0; viewerIdx < ConnectionViewers.Num(); viewerIdx++)
	{
		if (IsNetRelevantFor(Actor, ConnectionViewers[viewerIdx].InViewer, ConnectionViewers[viewerIdx].ViewTarget, ConnectionViewers[viewerIdx].ViewLocation))
		{
			return true;
		}
	}
	return false;
}

bool Driver::IsLevelInitalizedForActor(UNetDriver* Driver, const AActor* InActor, const UNetConnection* InConnection)
{
	if (!InActor || !InConnection) return false;

	const bool bCorrectWorld = Driver->WorldPackage != nullptr;

	bool bIsConnectionPC = false;

	const UNetConnection* const ParentConnection = InConnection->IsA(UChildConnection::StaticClass()) ? ((UChildConnection*)InConnection)->Parent : InConnection;

	if (InActor == ParentConnection->PlayerController)
	{
		bIsConnectionPC = true;
	}
	else
	{
		for (const UChildConnection* const ChildConnection : ParentConnection->Children)
		{
			if (InActor == ChildConnection->PlayerController)
			{
				bIsConnectionPC = true;
				break;
			}
		}
	}

	return bCorrectWorld || bIsConnectionPC;
}

int32 Driver::ServerReplicateActors_ProcessActors(UNetDriver* NetDriver, UNetConnection* Connection, TArray<FNetViewer>& ConnectionViewers, std::vector<FNetworkObjectInfo*> Actors, int32 FinalSortedCount, int32& OutUpdated) {
	int32 ActorUpdatesThisConnection = 0;
	int32 ActorUpdatesThisConnectionSent = 0;
	int32 FinalRelevantCount = 0;

	if (Connection) {

		for (FNetworkObjectInfo* ActorInfo : Actors)
			//for (int32 j = 0; j < FinalSortedCount; j++)
		{
			auto Actor = ActorInfo->Actor;
			bool bIsRelevant = false;

			if (Actor && Connection) {
				if (NetDriver->World != UWorld::GetWorld()) continue; // gulp

				UActorChannel* Channel = FindActorChannel(Connection, Actor);

				if (!Channel || Channel->Actor) {
					const bool bLevelInitializedForActor = IsLevelInitalizedForActor(NetDriver, Actor, Connection);

					if (bLevelInitializedForActor) {
						if (!Actor->bTearOff && (!Channel || NetDriver->Time - Channel->RelevantTime > 1.f))
						{
							if (IsActorRelevantToConnection(Actor, ConnectionViewers))
							{
								bIsRelevant = true;
							}
						}
					}

					const bool bIsRecentlyRelevant = bIsRelevant ||
						(Channel && NetDriver->Time - Channel->RelevantTime < NetDriver->RelevantTimeout) ||
						ActorInfo->bForceRelevantNextUpdate;

					ActorInfo->bForceRelevantNextUpdate = false;

					if (bIsRecentlyRelevant) {
						FinalRelevantCount++;


						if (Channel == NULL && NetDriver->GuidCache->SupportsObject(Actor->Class) && NetDriver->GuidCache->SupportsObject(Actor->bNetStartup ? Actor : GetArcheType(Actor))) { // todo :///

							if (bLevelInitializedForActor)
							{
								Channel = (UActorChannel*)CreateChannel(Connection, 2, true, -1);
								if (Channel)
									SetChannelActor(Channel, Actor);
							}
							else if (Actor->NetUpdateFrequency < 1.0f)
								ActorInfo->NextUpdateTime = UGameplayStatics::GetTimeSeconds(NetDriver->World) + 0.2f * UKismetMathLibrary::RandomFloat();
						}

						if (Channel)
						{
							if (bIsRelevant)
							{
								Channel->RelevantTime = NetDriver->Time + 0.5f * UKismetMathLibrary::RandomFloat();
							}

							//https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Engine/Private/DataChannel.cpp#L1618
							/*

							 (_QWORD *)(*(__int64 (__fastcall **)(_QWORD, _QWORD))(**(_QWORD **)(a1 + 0x28) + 664LL))(
					   *(_QWORD *)(a1 + 0x28),
					   '\0');
							*/

							//7FF7672879B0 ~ 1AE79B0
							//if((bool*)(*(__int64(__fastcall**)(__int64, __int64))(**(__int64**)(Channel + 0x28) + 0x298LL))(*(__int64*)(Channel + 0x28), '\0'))
							static bool (*IsNetReady)(UNetConnection * Connection, bool Saturate) = decltype(IsNetReady)(ImageBase + 0x1AE79B0);

							if (IsNetReady(Channel->Connection, 0))
							{
								//if (Channel->Connection->IsNetReady(0)) { 
								//if(Channel->)
								if (ReplicateActor(Channel)) {
									ActorUpdatesThisConnection++;

									const float MinOptimalDelta = 1.0f / Actor->NetUpdateFrequency;
									const float MaxOptimalDelta = UKismetMathLibrary::Max(1.0f / Actor->MinNetUpdateFrequency, MinOptimalDelta);
									const float DeltaBetweenReplications = (UGameplayStatics::GetTimeSeconds(NetDriver->World) - ActorInfo->LastNetReplicateTime);

									// Choose an optimal time, we choose 70% of the actual rate to allow frequency to go up if needed
									ActorInfo->OptimalNetUpdateDelta = UKismetMathLibrary::Clamp(DeltaBetweenReplications * 0.7f, MinOptimalDelta, MaxOptimalDelta);
									ActorInfo->LastNetReplicateTime = UGameplayStatics::GetTimeSeconds(NetDriver->World);
								}
								ActorUpdatesThisConnection++;
								OutUpdated++;
							}

							else {
								std::cout << "- Channel saturated, forcing pending update for " + Actor->GetName() << std::endl;
								Actor->ForceNetUpdate();
							}

						}
					}


					if ((!bIsRecentlyRelevant || Actor->bTearOff) && Channel != NULL)
					{
						if (!bLevelInitializedForActor || !Actor->bNetStartup) {
							CloseActorChannel(Channel);
						}
					}
				}
			}
		}
	}

	return FinalSortedCount;
}

bool Driver::ShouldActorGoDormant(AActor* Actor, const TArray<FNetViewer>& ConnectionViewers, UActorChannel* Channel, const float Time, const bool bLowNetBandwidth) {
	// need to check if its dormant
	if (Actor->NetDormancy <= ENetDormancy::DORM_Awake || !Channel) {
		return false;
	}

	if (Actor->NetDormancy == ENetDormancy::DORM_DormantPartial) {
		for (int32 viewerIdx = 0; viewerIdx < ConnectionViewers.Num(); viewerIdx++)
		{
			// epic just made this always return false lol (that makes it true)
			/*if (!Actor->GetNetDormancy(ConnectionViewers[viewerIdx].ViewLocation, ConnectionViewers[viewerIdx].ViewDir, ConnectionViewers[viewerIdx].InViewer, ConnectionViewers[viewerIdx].ViewTarget, Channel, Time, bLowNetBandwidth))
			{

			}*/

			return false;
		}
	}

	return true;
}

int32 Driver::ServerReplicateActors_PrioritizeActors(UNetDriver* Driver, UNetConnection* Connection, TArray<FNetViewer>& ConnectionViewers, std::vector<FNetworkObjectInfo*> ConsiderList, const bool bCPUStatured, std::vector<FNetworkObjectInfo*>& OutPriorityList)
{
	Driver->GetNetTag()++;

	for (int32 j = 0; j < Connection->SentTemporaries.Num(); j++)
	{
		Connection->SentTemporaries[j]->NetTag = Driver->GetNetTag();
	}

	Connection->GetTickCount()++;

	int32 FinalSortedCount = 0;
	int32 DeletedCount = 0;

	TWeakObjectPtr<UNetConnection> WeakConnection;
	WeakConnection.ObjectIndex = Connection->Index;
	WeakConnection.ObjectSerialNumber = UObject::GObjects->GetDecrytedObjPtr()[Connection->Index].SerialNumber;

	const int32 MaxSortedActors = ConsiderList.size(); //Ill get the other thing later

	if (MaxSortedActors > 0)
	{
		//Ill do getworld check later

		AGameNetworkManager* const NetworkManager = UWorld::GetWorld()->NetworkManager;

		for (FNetworkObjectInfo* ActorInfo : ConsiderList)
		{
			AActor* Actor = ActorInfo->Actor;

			UActorChannel* Channel = FindActorChannel(Connection, Actor);

			if (!Channel)
			{
				if (!IsLevelInitalizedForActor(Driver, Actor, Connection))
					continue;

				if (!IsActorRelevantToConnection(Actor, ConnectionViewers))
					continue;
			}

			UNetConnection* PriorityConnection = Connection;

			if (Actor->bOnlyRelevantToOwner)
			{
				bool bHasNullViewTarget = false;

				PriorityConnection = IsActorOwnedByAndRelevantToConnection(Actor, ConnectionViewers, bHasNullViewTarget);

				if (PriorityConnection == nullptr)
				{
					// Not owned by this connection, if we have a channel, close it, and continue
					// NOTE - We won't close the channel if any connection has a NULL view target.
					//	This is to give all connections a chance to own it
					if (!bHasNullViewTarget && Channel != NULL && Driver->Time - Channel->RelevantTime >= Driver->RelevantTimeout)
					{
						CloseActorChannel(Channel);
					}

					// This connection doesn't own this actor
					continue;
				}
			}
			else /*NOTIMPLEMETNED*/ {
				//if (ActorInfo->DormantConnections.Find(WeakConnection)) {
				//	continue; // ggs
				//}

				//// need to check if its dormant
				//if (ShouldActorGoDormant(Actor, ConnectionViewers, Channel, Driver->Time, false)) {
				//	//197 2080
				//	static void (*StartBecomingDormant)(UActorChannel * Channel) = decltype(StartBecomingDormant)(ImageBase + 0x1972080);
				//	StartBecomingDormant(Channel);
				//}
			}

			if (Actor->NetTag != Driver->GetNetTag())
			{
				//	std::cout << "Consider %s alwaysrelevant %d frequency %f" << std::endl;
				Actor->NetTag = Driver->GetNetTag();

				OutPriorityList.push_back(ActorInfo);

				FinalSortedCount++;


				//OutPriorityActors.push_back(OutPriorityList + FinalSortedCount);

				//OutPriorityList.push_back(ActorInfo);
				//LastPrioritizedActors.
			}
		}
	}

	//for (auto element : OutPriorityList)
	//{
	//	std::cout << element.ActorInfo->Actor->GetName() << std::endl;
	//}



	return FinalSortedCount;
}

int32 Driver::ServerReplicateActors(UNetDriver* Driver, float a2) {
	Driver->ReplicationFrame++;

	int32 Updated = 0;


	const int32 NumClientsToTick = ServerReplicateActors_PrepConnections(Driver, a2);

	if (NumClientsToTick == 0) return 0;

	bool bCPUSaturated = false;
	float ServerTickTime = 30.f;

	if (ServerTickTime == 0.f) {
		ServerTickTime = a2;
	}
	else {
		ServerTickTime = 1.f / ServerTickTime;
		bCPUSaturated = a2 > 1.2f * ServerTickTime;
	}


	std::vector<FNetworkObjectInfo*> ConsiderList = ServerReplicateActors_BuildConsiderList(Driver, ServerTickTime);

	TSet<UNetConnection*> ConnectionsToClose;

	for (int32 i = 0; i < Driver->ClientConnections.Num(); i++) {
		UNetConnection* Connection = Driver->ClientConnections[i];
		if (Connection) {



			if (i >= NumClientsToTick) {
				std::cout << "HEY TEST " << std::endl;
				for (int32 ConsiderIdx = 0; ConsiderIdx < ConsiderList.size(); ConsiderIdx++)
				{
					AActor* Actor = ConsiderList[ConsiderIdx]->Actor;

					if (Actor != NULL && !ConsiderList[ConsiderIdx]->bPendingNetUpdate)
					{
						UActorChannel* Channel = FindActorChannel(Connection, ConsiderList[ConsiderIdx]->WeakActor.Get());

						if (Channel != NULL && Channel->LastUpdateTime < ConsiderList[ConsiderIdx]->LastNetUpdateTime)
						{
							ConsiderList[ConsiderIdx]->bPendingNetUpdate = true;
						}
					}
				}
				Connection->TimeSensitive = false;
			}

			else if (Connection->ViewTarget) {
				// Make a list of viewers this connection should consider (this connection and children of this connection)
				TArray<FNetViewer>& ConnectionViewers = AWorldSettings::GetDefaultObj()->ReplicationViewers;
				ConnectionViewers.Clear(); // probally nopt the way

				FNetViewer NetViewer; // lazyy ahh

				NetViewer.Connection = Connection;
				NetViewer.InViewer = Connection->PlayerController ? Connection->PlayerController : Connection->OwningActor;
				NetViewer.ViewTarget = Connection->ViewTarget;
				NetViewer.ViewLocation = Connection->ViewTarget->K2_GetActorLocation();
				NetViewer.ViewDir = Connection->ViewTarget->K2_GetActorLocation();

				ConnectionViewers.Add(NetViewer);
				//new(ConnectionViewers)FNetViewer(Connection, DeltaTime);
				for (int32 ViewerIndex = 0; ViewerIndex < Connection->Children.Num(); ViewerIndex++)
				{
					if (Connection->Children[ViewerIndex]->ViewTarget != NULL)
					{
						UNetConnection* ChildrenConnection = Connection->Children[ViewerIndex];
						NetViewer.Connection = ChildrenConnection;
						NetViewer.InViewer = ChildrenConnection->PlayerController ? ChildrenConnection->PlayerController : ChildrenConnection->OwningActor;
						NetViewer.ViewTarget = ChildrenConnection->ViewTarget;
						NetViewer.ViewLocation = ChildrenConnection->ViewTarget->K2_GetActorLocation();
						NetViewer.ViewDir = ChildrenConnection->ViewTarget->K2_GetActorLocation();
						ConnectionViewers.Add(NetViewer);
					}
				}

				if (Connection->PlayerController) {
					SendClientAdjustment(Connection->PlayerController);


					/*	if (two > 0) {
							std::cout << "something?!?" << std::to_string(two) << std::endl;
						}*/
				}

				for (int32 ChildIdx = 0; ChildIdx < Connection->Children.Num(); ChildIdx++)
				{
					if (Connection->Children[ChildIdx]->PlayerController != NULL)
					{
						SendClientAdjustment(Connection->Children[ChildIdx]->PlayerController);
					}
				}

				// supposed to be outside this

				std::vector<FNetworkObjectInfo*> OutPriorityList = {};

				int32 FinalSortedCount = ServerReplicateActors_PrioritizeActors(Driver, Connection, ConnectionViewers, ConsiderList, false, OutPriorityList);
				int32 LastProcessedActor = ServerReplicateActors_ProcessActors(Driver, Connection, ConnectionViewers, OutPriorityList, FinalSortedCount, Updated);

				// i set it to false and doors just never need a update
				for (int32 k = LastProcessedActor; k < FinalSortedCount; k++)
				{
					if (!OutPriorityList[k])
					{
						// A deletion entry, skip it because we dont have anywhere to store a 'better give higher priority next time'
						continue;
					}

					AActor* Actor = OutPriorityList[k]->Actor;
					UActorChannel* Channel = FindActorChannel(Connection, Actor);

					if (Channel != NULL && Driver->Time - Channel->RelevantTime <= 1.f) {
						OutPriorityList[k]->bPendingNetUpdate = true;
					}
					else if (IsActorRelevantToConnection(Actor, ConnectionViewers)) {
						OutPriorityList[k]->bPendingNetUpdate = true;

						if (Channel != NULL) {
							Channel->RelevantTime = Driver->Time + 0.5f * UKismetMathLibrary::RandomFloat();
						}
					}
				}

				OutPriorityList.clear();
				ConnectionViewers.Clear(); // need to free but idrc 
			}
		}
	}

	ConsiderList.clear();
}

void Driver::TickFlush(UNetDriver* Driver, float a2) {
	if (Driver->ClientConnections.Num() > 0 && Driver->ClientConnections[0]->InternalAck == false)
	{

		ServerReplicateActors(Driver, a2);
	}

	return TickFlush_OG(Driver, a2);
}
