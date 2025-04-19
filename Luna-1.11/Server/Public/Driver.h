#pragma once
#include "..\framework.h"

class Driver {
private:
	Driver() = default;
public:
	static inline void (*CallPreReplication)(AActor* Actor, UNetDriver* NetDriver);
	static inline UChannel* (*CreateChannel)(UNetConnection* Connection, int, bool bOpenedLocally, int Idx);

	static inline void (*SetChannelActor)(UActorChannel* Channel, AActor* Actor);

	// sub_7FF76841E750(__int64 a1, __int64 a2, __int64 a3, __int64 a4) ~ 418/8 is index
	static inline bool (*IsNetRelevantFor)(AActor*, AActor*, AActor*, FVector&);
	static inline void (*CloseActorChannel)(UActorChannel*);

	static inline void (*SendClientAdjustment)(APlayerController* Controller);

	static inline bool (*ReplicateActor)(UActorChannel* Channel);

	// functions
	static FNetworkObjectList& GetNetworkObjectList(UNetDriver* Driver);
	static AActor* GetArcheType(AActor* Actor);
	static int32 ServerReplicateActors_PrepConnections(UNetDriver* NetDriver, float a2);
	static std::vector<FNetworkObjectInfo*> ServerReplicateActors_BuildConsiderList(UNetDriver* Driver, float a2);

	static UActorChannel* FindActorChannel(UNetConnection* Connection, AActor* Actor);

	// only here bc i cant call player controller, pawn and stuff in actor class
	// all this does is normally return this and the same with pc, pawn
	static AActor* GetNetOwner(AActor* Actor);

	// Returns true if this actor is owned by, and should replicate to *any* of the passed in connections
	static UNetConnection* IsActorOwnedByAndRelevantToConnection(AActor* Actor, const TArray<FNetViewer>& ConnectionViewers, bool& bOutHasNullViewTarget);

	static bool IsActorRelevantToConnection(AActor* Actor, TArray<FNetViewer>& ConnectionViewers);

	static bool IsLevelInitalizedForActor(UNetDriver* Driver, const AActor* InActor, const UNetConnection* InConnection);

	static int32 ServerReplicateActors_ProcessActors(UNetDriver* NetDriver, UNetConnection* Connection, TArray<FNetViewer>& ConnectionViewers, std::vector<FNetworkObjectInfo*> Actors, int32 FinalSortedCount, int32& OutUpdated);

	static bool ShouldActorGoDormant(AActor* Actor, const TArray<FNetViewer>& ConnectionViewers, UActorChannel* Channel, const float Time, const bool bLowNetBandwidth);
	static int32 ServerReplicateActors_PrioritizeActors(UNetDriver* Driver, UNetConnection* Connection, TArray<FNetViewer>& ConnectionViewers, std::vector<FNetworkObjectInfo*> ConsiderList, const bool bCPUStatured, std::vector<FNetworkObjectInfo*>& OutPriorityList);

	static int32 ServerReplicateActors(UNetDriver* Driver, float a2);

	static inline void (*TickFlush_OG)(UNetDriver* Driver, float a2);

	static void TickFlush(UNetDriver* Driver, float a2);
};


//

// need to clean up this also uses FNetBitWriter but i cant be btohered i hope it doesnt effect much
//class FOutBunch {
//public:
//	// Variables.
//	FOutBunch* Next;
//	UChannel* Channel;
//	double					Time;
//	bool					ReceivedAck;
//	int32					ChIndex;
//	int32					ChType;
//	int32					ChSequence;
//	int32					PacketId;
//	uint8					bOpen;
//	uint8					bClose;
//	uint8					bDormant;
//	uint8					bIsReplicationPaused;   // Replication on this channel is being paused by the server
//	uint8					bReliable;
//	uint8					bPartial;				// Not a complete bunch
//	uint8					bPartialInitial;		// The first bunch of a partial bunch
//	uint8					bPartialFinal;			// The final bunch of a partial bunch
//	uint8					bHasPackageMapExports;	// This bunch has networkGUID name/id pairs
//	uint8					bHasMustBeMappedGUIDs;	// This bunch has guids that must be mapped before we can process this bunch
//
//	FOutBunch(class UChannel* InChannel, bool bClose);
//};
//
//enum class EChannelCloseReason : uint8
//{
//	Destroyed,
//	Dormancy,
//	LevelUnloaded,
//	Relevancy,
//	TearOff,
//	/* reserved */
//	MAX = 15		// this value is used for serialization, modifying it may require a network version change
//};
//
////https://github.com/EpicGames/UnrealEngine/blob/4.19/Engine/Source/Runtime/Core/Public/Misc/NetworkGuid.h
//class FNetworkGUID
//{
//public:
//
//	uint32 Value;
//
//public:
//	// idrk
//	std::string ToString() const
//	{
//		return std::to_string(Value);
//	}
//};
//
//struct FActorDestructionInfo
//{
//public:
//	FActorDestructionInfo()
//		: Reason(EChannelCloseReason::Destroyed)
//		, bIgnoreDistanceCulling(false)
//	{}
//
//	TWeakObjectPtr<ULevel> Level;
//	TWeakObjectPtr<UObject> ObjOuter;
//	FVector DestroyedPosition;
//	FNetworkGUID NetGUID;
//	FString PathName;
//	FName StreamingLevelName;
//	EChannelCloseReason Reason;
//
//	/** When true the destruction info data will be sent even if the viewers are not close to the actor */
//	bool bIgnoreDistanceCulling;
//
//	/*void CountBytes(FArchive& Ar)
//	{
//		PathName.CountBytes(Ar);
//	}*/
//};


	


	

	

	//inline UActorChannel* FindWeakActorChannel(UNetConnection* Connection, TMap<TWeakObjectPtr<AActor>, class UActorChannel*> ActorMap, AActor* WeakActpr) {
	//	for (const TPair<TWeakObjectPtr<AActor>, UActorChannel*>& Pair : ActorMap)
	//	{
	//		TWeakObjectPtr<AActor> ActorKey = Pair.First;

	//
	//		if (AActor* Actor = WeakActpr)
	//		{
	//			if (Actor == ActorKey.Get())
	//			{
	//				return (UActorChannel*)Pair.Second->Class;
	//			}
	//		}
	//	}

	//	return nullptr;
	//}

	
	

	

	
	
