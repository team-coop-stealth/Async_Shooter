// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_Steamworks.generated.h"

/**
 * 
 */
UCLASS()
class ASYNC_SHOOTER_API UFL_Steamworks : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = "SteamFriends")
	static FString GetPersonaName();
};
