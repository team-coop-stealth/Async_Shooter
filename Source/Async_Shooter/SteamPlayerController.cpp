// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamPlayerController.h"
#include "FL_SteamUtils.h"

int32 ASteamPlayerController::GetPlayerIndex()
{
	if (GetGameInstance())
	{
		ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
		if (LocalPlayer)
		{
			return LocalPlayer->GetLocalPlayerIndex();
		}
	}
	return -1; // Invalid index
}

FInputHandle* ASteamPlayerController::GetInputHandleByIndex(int32 Index)
{
	if (InputHandles.IsValidIndex(Index)) {
		return &InputHandles[Index];
	}
	return nullptr;
}

void ASteamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UFL_SteamUtils::EnableWarningMessageHook();
	UFL_SteamInput::Init();
	DigitalActionHandles = TMap<FString, TMap<FString, FInputDigitalActionHandle>>();
	AnalogActionHandles = TMap<FString, TMap<FString, FInputAnalogActionHandle>>();
	for (FDynamicActionSet ActionSet : InputActionSets)
	{
		FInputActionSetHandle actionSetHandle = UFL_SteamInput::GetActionSetHandle(ActionSet.ActionSetName);
		ActionSetHandles.Add(ActionSet.ActionSetName, actionSetHandle);
		TMap<FString, FInputDigitalActionHandle> digitalActions = TMap<FString, FInputDigitalActionHandle>();
		for (FString DigitalAction : ActionSet.DigitalActions)
		{
			digitalActions.Add(DigitalAction, UFL_SteamInput::GetDigitalActionHandle(DigitalAction));
			DigitalActionState.Add(DigitalAction, false);
			DigitalActionPressedDuration.Add(DigitalAction, 0);
			DigitalActionReleasedDuration.Add(DigitalAction, 0);
		}
		DigitalActionHandles.Add(ActionSet.ActionSetName, digitalActions);

		TMap<FString, FInputAnalogActionHandle> analogActions = TMap<FString, FInputAnalogActionHandle>();
		for (FString AnalogAction : ActionSet.AnalogActions)
		{
			analogActions.Add(AnalogAction, UFL_SteamInput::GetAnalogActionHandle(AnalogAction));
		}
		AnalogActionHandles.Add(ActionSet.ActionSetName, analogActions);
	}
}

void ASteamPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (EndPlayReason == EEndPlayReason::Destroyed) {
		UFL_SteamInput::Shutdown();
	}
}

void ASteamPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UFL_SteamInput::RunFrame();

	//Update Connected Controllers
	InputHandles = UFL_SteamInput::GetConnectedControllers();

	//Does play have a Steam Input controller
	FInputHandle* controller = GetInputHandleByIndex(GetPlayerIndex());
	if (controller == nullptr) {
		return;
	}
	//Activate Current Action Set Handle
	FInputActionSetHandle* currentActionSetHandle = ActionSetHandles.Find(CurrentInputActionSet);
	if (currentActionSetHandle == nullptr) {
		return;
	}
	UFL_SteamInput::ActivateActionSet(*controller, *currentActionSetHandle);
	
	//Await Inputs from Controller
	TMap<FString, FInputDigitalActionHandle>* digitalInputAction = DigitalActionHandles.Find(CurrentInputActionSet);
	for (TPair<FString, FInputDigitalActionHandle> pair : *digitalInputAction) {
		FInputDigitalActionData digitalData = UFL_SteamInput::GetDigitalActionData(*controller, pair.Value);
		bool lastState = DigitalActionState.FindOrAdd(pair.Key);
		float pressedDur = DigitalActionPressedDuration.FindOrAdd(pair.Key);
		float releasedDur = DigitalActionPressedDuration.FindOrAdd(pair.Key);
		if (!lastState && digitalData.bState) {
			DigitalActionPressedDuration.Add(pair.Key, pressedDur + DeltaTime);
			DigitalActionReleasedDuration.Add(pair.Key, 0);
			OnSteamDigitalInputJustPressed.Broadcast(pair.Key);
		}
		else if (lastState && digitalData.bState) {
			float newPressedDur = pressedDur + DeltaTime;
			DigitalActionPressedDuration.Add(pair.Key, newPressedDur);
			OnSteamDigitalInputPressed.Broadcast(pair.Key, newPressedDur);
		}
		else if (lastState && !digitalData.bState) {
			DigitalActionReleasedDuration.Add(pair.Key, releasedDur + DeltaTime);
			DigitalActionPressedDuration.Add(pair.Key, 0);
			OnSteamDigitalInputJustReleased.Broadcast(pair.Key);
		}
		else {
			float newReleasedDur = releasedDur + DeltaTime;
			DigitalActionPressedDuration.Add(pair.Key, newReleasedDur);
			OnSteamDigitalInputReleased.Broadcast(pair.Key, newReleasedDur);
		}
		DigitalActionState.Add(pair.Key, digitalData.bState);
	}

	TMap<FString, FInputAnalogActionHandle>* analogInputAction = AnalogActionHandles.Find(CurrentInputActionSet);
	for (TPair<FString, FInputAnalogActionHandle> pair : *analogInputAction) {
		FInputAnalogActionData analogData = UFL_SteamInput::GetAnalogActionData(*controller, pair.Value);
		if (analogData.bActive) {
			OnSteamAnalogInput.Broadcast(pair.Key, analogData.state, analogData.eMode);
		}
	}
}
