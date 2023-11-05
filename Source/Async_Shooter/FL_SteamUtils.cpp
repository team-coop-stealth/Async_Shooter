// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_SteamUtils.h"

DEFINE_LOG_CATEGORY(Steamworks);

extern "C" void S_CALLTYPE SteamAPIDebugTextHook(int nSeverity, const char* pchDebugText)
{

	FString DebugText = FString(ANSI_TO_TCHAR(pchDebugText));
	if (nSeverity == 0) {
		UE_LOG(Steamworks, Display, TEXT("%s"), *DebugText);
	}
	else if (nSeverity == 1) {
		UE_LOG(Steamworks, Warning, TEXT("%s"), *DebugText);
	}

}

void UFL_SteamUtils::EnableWarningMessageHook()
{
	SteamUtils()->SetWarningMessageHook(&SteamAPIDebugTextHook);
}

void UFL_SteamUtils::DisableWarningMessageHook()
{
	SteamUtils()->SetWarningMessageHook(NULL);
}
