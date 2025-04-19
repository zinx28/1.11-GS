#pragma once

class GameMode {
private:
	GameMode() = default;
public: 
	static inline UNetDriver* (*CreateNetDriver)(UEngine* Engine, UWorld*, FName NetDriverDefinition);
	static inline bool (*InitListen)(UNetDriver* IpNetDriver, UWorld* InNotify, FURL& LocalURL, bool bReuseAddressAndPort, FString& Error);
	static inline void (*SetWorld)(UNetDriver* Driver, UWorld* World);

	static inline bool bWorldisReady = false;
	static inline bool (*ReadyToStartMatch_OG)(AFortGameModeAthena* GameMode);


	static bool ReadyToStartMatch(AFortGameModeAthena* GameMode);
	static APawn* SpawnDefaultPawnFor(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* Controller, AActor* StartSpot);

	static inline void (*HandleStartingNewPlayer_OG)(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* Controller);

	static void HandleStartingNewPlayer(AFortGameModeAthena* GameMode, AFortPlayerControllerAthena* Controller);
};