// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_SteamFriends.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include "Steam/isteamfriends.h"
#pragma warning(pop)

FString UFL_SteamFriends::GetPersonaName()
{
	return (FString(SteamFriends()->GetPersonaName()));
}