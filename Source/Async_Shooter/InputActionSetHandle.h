// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Steam/isteaminput.h"
#include "InputActionSetHandle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputActionSetHandle
{
	GENERATED_BODY()
	InputActionSetHandle_t HandleValue;
};
