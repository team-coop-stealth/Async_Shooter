// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_SteamFriends.generated.h"

/**
 * 
 */
UCLASS()
class ASYNC_SHOOTER_API UFL_SteamFriends : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamFriends")
	/**
	* Gets the current user's persona (display) name.
	* This is the same name that is displayed the user's community profile page.
	* To get the persona name of other users use GetFriendPersonaName.
	* @return The current user's persona name in UTF-8 format. Guaranteed to not be NULL.
	*/
	static FString GetPersonaName();
};
