// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputMotionData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputMotionData
{
	GENERATED_BODY()
	
    UPROPERTY(BlueprintReadWrite, Category = "InputMotionData")
    FQuat RotationQuat = FQuat::Identity;

    UPROPERTY(BlueprintReadWrite, Category = "InputMotionData")
    FVector PositionalAcceleration = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite, Category = "InputMotionData")
    FVector AngularVelocity = FVector::ZeroVector;
};
