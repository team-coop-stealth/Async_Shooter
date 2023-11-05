// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Steam/isteamutils.h"

#include "FL_SteamUtils.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Steamworks, Log, All);

/**
 * 
 */
UCLASS(minimalapi)
class UFL_SteamUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamUtils")
	static void EnableWarningMessageHook();
	
	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamUtils")
	static void DisableWarningMessageHook();
	
};
