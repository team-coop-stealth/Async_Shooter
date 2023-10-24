// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_Steamworks.h"
#include "Steam/isteamfriends.h"

FString UFL_Steamworks::GetPersonaName()
{
	return ( FString(SteamFriends()->GetPersonaName()) );
}
