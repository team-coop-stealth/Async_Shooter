// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/steam_api.h"
#pragma warning(pop)

#include "SteamGameModeBase.generated.h"

#define RAW_APP_ID "480"

/**
 * 
 */
UCLASS(minimalapi)
class ASteamGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:
	ASteamGameModeBase();

	static constexpr const char* APP_ID = RAW_APP_ID;
	CSteamID MyId;
};
