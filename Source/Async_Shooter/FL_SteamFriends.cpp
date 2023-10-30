// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_SteamFriends.h"
#include "Steam/isteamfriends.h"

FString UFL_SteamFriends::GetPersonaName()
{
	return (FString(SteamFriends()->GetPersonaName()));
}