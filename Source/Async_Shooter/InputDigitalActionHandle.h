// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Steam/isteaminput.h"
#include "InputDigitalActionHandle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputDigitalActionHandle
{
	GENERATED_BODY()
	InputDigitalActionHandle_t HandleValue;
};
