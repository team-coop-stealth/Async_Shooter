// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

void ASteamGameModeBase::BeginPlay() {
	Super::BeginPlay();

	FFileHelper::SaveStringToFile(TEXT(RAW_APP_ID), TEXT("steam_appid.txt"));

	SteamAPI_RestartAppIfNecessary(atoi(APP_ID));

	if (SteamAPI_Init()) {
		MyId = SteamUser()->GetSteamID();
	}
}

ASteamGameModeBase::ASteamGameModeBase()
	: Super()
{

}
