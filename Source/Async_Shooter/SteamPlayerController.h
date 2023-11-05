// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FL_SteamInput.h"
#include "SteamPlayerController.generated.h"


USTRUCT(BlueprintType)
struct FDynamicActionSet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ActionSetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> DigitalActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> AnalogActions;
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSteamDigitalInput, FString, InputAction);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSteamDigitalInputKeep, FString, InputAction, float, ElapsedSeconds);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSteamAnalogInput, FString, InputAction, FVector2D, State,ECInputSourceMode, InputSourceMode);

/**
 * 
 */
UCLASS(minimalapi)
class ASteamPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	TArray<FInputHandle> InputHandles;
	TMap<FString, FInputActionSetHandle> ActionSetHandles;
	TMap<FString, TMap<FString, FInputDigitalActionHandle>> DigitalActionHandles;
	TMap<FString, TMap<FString, FInputAnalogActionHandle>> AnalogActionHandles;
	TMap<FString, bool> DigitalActionState;
	TMap<FString, float> DigitalActionPressedDuration;
	TMap<FString, float> DigitalActionReleasedDuration;
	int32 GetPlayerIndex();
	FInputHandle* GetInputHandleByIndex(int32 Index);
public:
	UPROPERTY(BlueprintAssignable)
	FSteamDigitalInputKeep OnSteamDigitalInputPressed;

	UPROPERTY(BlueprintAssignable)
	FSteamDigitalInput OnSteamDigitalInputJustPressed;

	UPROPERTY(BlueprintAssignable)
	FSteamDigitalInputKeep OnSteamDigitalInputReleased;

	UPROPERTY(BlueprintAssignable)
	FSteamDigitalInput OnSteamDigitalInputJustReleased;

	UPROPERTY(BlueprintAssignable)
	FSteamAnalogInput OnSteamAnalogInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDynamicActionSet> InputActionSets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString CurrentInputActionSet;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;
};
