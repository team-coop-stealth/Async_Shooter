// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Steam/isteaminput.h"
#include "InputAnalogActionHandle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputAnalogActionHandle
{
	GENERATED_BODY()
	InputAnalogActionHandle_t HandleValue;
};
