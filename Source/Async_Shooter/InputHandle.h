// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Steam/isteaminput.h"
#include "InputHandle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputHandle
{
	GENERATED_BODY()
	InputHandle_t HandleValue;
};
