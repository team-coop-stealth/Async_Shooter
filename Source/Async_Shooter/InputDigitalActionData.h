// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputDigitalActionData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputDigitalActionData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	bool bState = false;
	UPROPERTY(BlueprintReadOnly)
	bool bActive = false;
};
