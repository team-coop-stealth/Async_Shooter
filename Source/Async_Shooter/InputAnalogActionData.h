// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Steam/isteaminput.h"
#include "InputAnalogActionData.generated.h"

UENUM(BlueprintType)
enum class ECInputSourceMode : uint8
{
	None			UMETA(DisplayName = "None"),
	Dpad			UMETA(DisplayName = "Dpad"),
	Buttons			UMETA(DisplayName = "Buttons"),
	FourButtons		UMETA(DisplayName = "FourButtons"),
	AbsoluteMouse	UMETA(DisplayName = "AbsoluteMouse"),
	RelativeMouse	UMETA(DisplayName = "RelativeMouse"),
	JoystickMove	UMETA(DisplayName = "JoystickMove"),
	JoystickMouse	UMETA(DisplayName = "JoystickMouse"),
	JoystickCamera	UMETA(DisplayName = "JoystickCamera"),
	ScrollWheel		UMETA(DisplayName = "ScrollWheel"),
	Trigger			UMETA(DisplayName = "Trigger"),
	TouchMenu		UMETA(DisplayName = "TouchMenu"),
	MouseJoystick	UMETA(DisplayName = "MouseJoystick"),
	MouseRegion		UMETA(DisplayName = "MouseRegion"),
	RadialMenu		UMETA(DisplayName = "RadialMenu"),
	SingleButton	UMETA(DisplayName = "SingleButton"),
	Switches		UMETA(DisplayName = "Switches"),
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInputAnalogActionData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	ECInputSourceMode eMode = ECInputSourceMode::None;
	UPROPERTY(BlueprintReadOnly)
	FVector2D state = FVector2D::ZeroVector;
	UPROPERTY(BlueprintReadOnly)
	bool bActive = false;
};

