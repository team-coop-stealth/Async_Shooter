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

FString ASteamPlayerController::GetCurrentGlyphForAction(FString Action)
{
	TMap<FString, DigitalInputAction>* currentDigitalGlyphs = DigitalActionHandles.Find(CurrentInputActionSet);
	if (currentDigitalGlyphs != nullptr && currentDigitalGlyphs->Contains(Action)) {
		return currentDigitalGlyphs->Find(Action)->GlyphPath;
	}
	TMap<FString, AnalogInputAction>* currentAnalogGlyphs = AnalogActionHandles.Find(CurrentInputActionSet);
	if (currentAnalogGlyphs != nullptr && currentAnalogGlyphs->Contains(Action)) {
		return currentAnalogGlyphs->Find(Action)->GlyphPath;
	}
	return "";
}

void ASteamPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UFL_SteamInput::Init();
	UFL_SteamUtils::EnableWarningMessageHook();
	DigitalActionHandles = TMap<FString, TMap<FString, DigitalInputAction>>();
	AnalogActionHandles = TMap<FString, TMap<FString, AnalogInputAction>>();
	for (FDynamicActionSet ActionSet : InputActionSets)
	{
		FInputActionSetHandle actionSetHandle = UFL_SteamInput::GetActionSetHandle(ActionSet.ActionSetName);
		ActionSetHandles.Add(ActionSet.ActionSetName, actionSetHandle);
		TMap<FString, DigitalInputAction> digitalActions = TMap<FString, DigitalInputAction>();
		for (FString DigitalAction : ActionSet.DigitalActions)
		{
			DigitalInputAction inputAction = DigitalInputAction();
			inputAction.Handle = UFL_SteamInput::GetDigitalActionHandle(DigitalAction);
			inputAction.GlyphPath = "";
			digitalActions.Add(DigitalAction, inputAction);
			DigitalActionState.Add(DigitalAction, false);
			DigitalActionPressedDuration.Add(DigitalAction, 0);
			DigitalActionReleasedDuration.Add(DigitalAction, 0);
		}
		DigitalActionHandles.Add(ActionSet.ActionSetName, digitalActions);

		TMap<FString, AnalogInputAction> analogActions = TMap<FString, AnalogInputAction>();
		for (FString AnalogAction : ActionSet.AnalogActions)
		{
			AnalogInputAction inputAction = AnalogInputAction();
			inputAction.Handle = UFL_SteamInput::GetAnalogActionHandle(AnalogAction);
			inputAction.GlyphPath = "";
			analogActions.Add(AnalogAction, inputAction);
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

	int32 oldNumberOfControllers = InputHandles.Num();

	//Update Connected Controllers
	InputHandles = UFL_SteamInput::GetConnectedControllers();

	if (oldNumberOfControllers == 0 && InputHandles.Num() > 0) {
		UFL_SteamInput::Init();
	}
	else if(oldNumberOfControllers > 0 && InputHandles.Num() == 0) {
		UFL_SteamInput::Shutdown();
	}

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
	
	//Await Inputs from Controller and updates Glyph path
	TMap<FString, DigitalInputAction>* digitalInputAction = DigitalActionHandles.Find(CurrentInputActionSet);
	for (TPair<FString, DigitalInputAction> pair : *digitalInputAction) {
		//Digital Input
		FInputDigitalActionData digitalData = UFL_SteamInput::GetDigitalActionData(*controller, pair.Value.Handle);
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
		//Get Digital Input Glyph Locations
		TArray<ECInputActionOrigin> actionOrigins = UFL_SteamInput::GetDigitalActionOrigins(*controller, *currentActionSetHandle, pair.Value.Handle);
		if (actionOrigins.Num() != 0) {
			pair.Value.GlyphPath = UFL_SteamInput::GetGlyphPNGForActionOrigin(actionOrigins[0], ECSteamInputGlyphSize::k_ESteamInputGlyphSize_Medium, 0);
			digitalInputAction->Remove(pair.Key);
			digitalInputAction->Add(pair.Key, pair.Value);
		}
	}

	TMap<FString, AnalogInputAction>* analogInputAction = AnalogActionHandles.Find(CurrentInputActionSet);
	for (TPair<FString, AnalogInputAction> pair : *analogInputAction) {
		//Analog Input
		FInputAnalogActionData analogData = UFL_SteamInput::GetAnalogActionData(*controller, pair.Value.Handle);
		if (analogData.bActive) {
			OnSteamAnalogInput.Broadcast(pair.Key, analogData.state, analogData.eMode);
		}
		//Get Analog Input Glyph Locations
		TArray<ECInputActionOrigin> actionOrigins = UFL_SteamInput::GetAnalogActionOrigins(*controller, *currentActionSetHandle, pair.Value.Handle);
		if (actionOrigins.Num() != 0) {
			pair.Value.GlyphPath = UFL_SteamInput::GetGlyphPNGForActionOrigin(actionOrigins[0], ECSteamInputGlyphSize::k_ESteamInputGlyphSize_Medium, 0);
			analogInputAction->Remove(pair.Key);
			analogInputAction->Add(pair.Key, pair.Value);
		}
	}
}
