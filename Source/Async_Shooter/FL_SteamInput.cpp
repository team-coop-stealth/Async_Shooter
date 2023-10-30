// Fill out your copyright notice in the Description page of Project Settings.


#include "FL_SteamInput.h"
#include <iostream>

void UFL_SteamInput::ActivateActionSet(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle)
{
	SteamInput()->ActivateActionSet(_inputHandle.HandleValue, _inputActionSetHandle.HandleValue);
}

void UFL_SteamInput::ActivateActionSetLayer(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle)
{
	SteamInput()->ActivateActionSetLayer(_inputHandle.HandleValue, _inputActionSetHandle.HandleValue);
}

void UFL_SteamInput::DeactivateActionSetLayer(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle)
{
	SteamInput()->DeactivateActionSetLayer(_inputHandle.HandleValue, _inputActionSetHandle.HandleValue);
}

void UFL_SteamInput::DeactivateAllActionSetLayers(FInputHandle _inputHandle)
{
	SteamInput()->DeactivateAllActionSetLayers(_inputHandle.HandleValue);
}

TArray<FInputActionSetHandle> UFL_SteamInput::GetActiveActionSetLayers(FInputHandle _inputHandle)
{
	TArray<FInputActionSetHandle> actionSetLayers = TArray<FInputActionSetHandle>();
	InputActionSetHandle_t* handles = new InputActionSetHandle_t[STEAM_INPUT_MAX_ACTIVE_LAYERS];
	int size = SteamInput()->GetActiveActionSetLayers(_inputHandle.HandleValue, handles);
	for (size_t i = 0; i < size; i++)
	{
		FInputActionSetHandle handle = FInputActionSetHandle();
		handle.HandleValue = handles[i];
		actionSetLayers.Add(handle);
	}
	delete[] handles;
	return actionSetLayers;
}

FInputActionSetHandle UFL_SteamInput::GetActionSetHandle(FString _actionSetName)
{
	FInputActionSetHandle actionSetHandle = FInputActionSetHandle();
	const char* name = TCHAR_TO_UTF8(*_actionSetName);
	actionSetHandle.HandleValue = SteamInput()->GetActionSetHandle(name);
	return actionSetHandle;
}

FInputAnalogActionData UFL_SteamInput::GetAnalogActionData(FInputHandle _inputHandle, FInputAnalogActionHandle _inputAnalogActionHandle)
{
	FInputAnalogActionData analogActionData = FInputAnalogActionData();
	InputAnalogActionData_t data = SteamInput()->GetAnalogActionData(_inputHandle.HandleValue, _inputAnalogActionHandle.HandleValue);
	analogActionData.bActive = data.bActive;
	analogActionData.eMode = ECInputSourceMode(data.eMode);
	analogActionData.state = FVector2D(data.x, data.y);
	return analogActionData;
}

FInputAnalogActionHandle UFL_SteamInput::GetAnalogActionHandle(FString _actionName)
{
	FInputAnalogActionHandle analogActionHandle = FInputAnalogActionHandle();
	analogActionHandle.HandleValue = SteamInput()->GetAnalogActionHandle(TCHAR_TO_UTF8(*_actionName));
	return analogActionHandle;
}

TArray<ECInputActionOrigin> UFL_SteamInput::GetAnalogActionOrigins(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle, FInputAnalogActionHandle _inputAnalogActionHandle)
{
	TArray<ECInputActionOrigin> actionOrigins = TArray<ECInputActionOrigin>();
	EInputActionOrigin* origins = new EInputActionOrigin[STEAM_INPUT_MAX_ORIGINS];
	int size = SteamInput()->GetAnalogActionOrigins(_inputHandle.HandleValue, _inputActionSetHandle.HandleValue, _inputAnalogActionHandle.HandleValue, origins);
	for (size_t i = 0; i < size; i++)
	{
		ECInputActionOrigin origin = ECInputActionOrigin(origins[i]);
		actionOrigins.Add(origin);
	}
	delete[] origins;
	return actionOrigins;
}

TArray<FInputHandle> UFL_SteamInput::GetConnectedControllers()
{
	TArray<FInputHandle> controllers = TArray<FInputHandle>();
	InputHandle_t* handles = new InputHandle_t[STEAM_INPUT_MAX_COUNT];
	int size = SteamInput()->GetConnectedControllers(handles);
	for (size_t i = 0; i < size; i++)
	{
		FInputHandle handle = FInputHandle();
		handle.HandleValue = handles[i];
		controllers.Add(handle);
	}
	delete[] handles;
	return controllers;
}

FInputHandle UFL_SteamInput::GetControllerForGamepadIndex(int32 _index)
{
	FInputHandle controller = FInputHandle();
	InputHandle_t h = SteamInput()->GetControllerForGamepadIndex(_index);
	controller.HandleValue = h;
	return controller;
}

FInputActionSetHandle UFL_SteamInput::GetCurrentActionSet(FInputHandle _inputHandle)
{
	FInputActionSetHandle actionSetHandle = FInputActionSetHandle();
	actionSetHandle.HandleValue = SteamInput()->GetCurrentActionSet(_inputHandle.HandleValue);
	return actionSetHandle;
}

FInputDigitalActionData UFL_SteamInput::GetDigitalActionData(FInputHandle _inputHandle, FInputDigitalActionHandle _digitalActionHandle)
{
	FInputDigitalActionData digitalActionData = FInputDigitalActionData();
	InputDigitalActionData_t data = SteamInput()->GetDigitalActionData(_inputHandle.HandleValue, _digitalActionHandle.HandleValue);
	digitalActionData.bActive = data.bActive;
	digitalActionData.bState = data.bState;
	return digitalActionData;
}

FInputDigitalActionHandle UFL_SteamInput::GetDigitalActionHandle(FString _actionName)
{
	FInputDigitalActionHandle digitalActionHandle = FInputDigitalActionHandle();
	digitalActionHandle.HandleValue = SteamInput()->GetDigitalActionHandle(TCHAR_TO_UTF8(*_actionName));
	return digitalActionHandle;
}

TArray<ECInputActionOrigin> UFL_SteamInput::GetDigitalActionOrigins(FInputHandle _inputHandle, FInputActionSetHandle _actionSetHandle, FInputDigitalActionHandle _digitalActionHandle)
{
	TArray<ECInputActionOrigin> digitalActionOrigins = TArray<ECInputActionOrigin>();
	EInputActionOrigin* origins = new EInputActionOrigin[STEAM_INPUT_MAX_ORIGINS];
	int size = SteamInput()->GetDigitalActionOrigins(_inputHandle.HandleValue, _actionSetHandle.HandleValue, _digitalActionHandle.HandleValue, origins);
	for (size_t i = 0; i < size; i++)
	{
		ECInputActionOrigin origin = ECInputActionOrigin(origins[i]);
		digitalActionOrigins.Add(origin);
	}
	delete[] origins;
	return digitalActionOrigins;
}

int32 UFL_SteamInput::GetGamepadIndexForController(FInputHandle _controllerHandle)
{
	return SteamInput()->GetGamepadIndexForController(_controllerHandle.HandleValue);
}

FString UFL_SteamInput::GetGlyphPNGForActionOrigin(ECInputActionOrigin _origin, ECSteamInputGlyphSize _glyphSize, int32 _flags)
{
	return SteamInput()->GetGlyphPNGForActionOrigin(EInputActionOrigin(_origin), ESteamInputGlyphSize(_glyphSize), _flags);
}

FString UFL_SteamInput::GetGlyphSVGForActionOrigin(ECInputActionOrigin _origin, int32 _flags)
{
	return SteamInput()->GetGlyphSVGForActionOrigin(EInputActionOrigin(_origin), _flags);
}

ECSteamInputType UFL_SteamInput::GetInputTypeForHandle(FInputHandle _inputHandle)
{
	ECSteamInputType inputType = ECSteamInputType(SteamInput()->GetInputTypeForHandle(_inputHandle.HandleValue));
	return inputType;
}

FInputMotionData UFL_SteamInput::GetMotionData(FInputHandle _inputHandle)
{
	FInputMotionData motionData = FInputMotionData();
	InputMotionData_t data = SteamInput()->GetMotionData(_inputHandle.HandleValue);
	motionData.AngularVelocity = FVector(data.rotVelX, data.rotVelY, data.rotVelZ);
	motionData.PositionalAcceleration = FVector(data.posAccelX, data.posAccelY, data.posAccelZ);
	motionData.RotationQuat = FQuat(data.rotQuatX, data.rotQuatY, data.rotQuatZ, data.rotQuatW);
	return motionData;
}

FString UFL_SteamInput::GetStringForActionOrigin(ECInputActionOrigin _origin)
{
	return FString(SteamInput()->GetStringForActionOrigin(EInputActionOrigin(_origin)));
}

bool UFL_SteamInput::Init()
{
	return SteamInput()->Init(false);
}

void UFL_SteamInput::RunFrame()
{
	SteamInput()->RunFrame();
}

void UFL_SteamInput::SetLEDColor(FInputHandle _inputHandle, FColor _color, ECSteamControllerLEDFlag _flags)
{
	SteamInput()->SetLEDColor(_inputHandle.HandleValue, _color.R, _color.G, _color.B, static_cast<unsigned int>(_flags));
}

bool UFL_SteamInput::ShowBindingPanel(FInputHandle _inputHandle)
{
	return SteamInput()->ShowBindingPanel(_inputHandle.HandleValue);
}

bool UFL_SteamInput::Shutdown()
{
	return SteamInput()->Shutdown();
}

void UFL_SteamInput::StopAnalogActionMomentum(FInputHandle _inputHandle, FInputAnalogActionHandle _action)
{
	SteamInput()->StopAnalogActionMomentum(_inputHandle.HandleValue, _action.HandleValue);
}

void UFL_SteamInput::TriggerSimpleHapticEvent(FInputHandle _inputHandle, ECControllerHapticLocation _hapticLocation, int32 _intensity, char _gainDB, int32 _otherIntensity, char _otherGainDB)
{
	SteamInput()->TriggerSimpleHapticEvent(_inputHandle.HandleValue, EControllerHapticLocation(_hapticLocation), _intensity, _gainDB, _otherIntensity, _otherGainDB);
}

void UFL_SteamInput::Legacy_TriggerHapticPulse(FInputHandle _inputHandle, ECSteamControllerPad _targetPad, int32 _durationMicroSec)
{
	SteamInput()->Legacy_TriggerHapticPulse(_inputHandle.HandleValue, ESteamControllerPad(_targetPad), _durationMicroSec);
}

void UFL_SteamInput::Legacy_TriggerRepeatedHapticPulse(FInputHandle _inputHandle, ECSteamControllerPad _targetPad, int32 _durationMicroSec, int32 _offMicroSec, int32 _repeat, int32 _flags)
{
	SteamInput()->Legacy_TriggerRepeatedHapticPulse(_inputHandle.HandleValue, ESteamControllerPad(_targetPad), _durationMicroSec, _offMicroSec, _repeat, _flags);
}

void UFL_SteamInput::TriggerVibration(FInputHandle _inputHandle, int32 _leftSpeed, int32 _rightSpeed)
{
	SteamInput()->TriggerVibration(_inputHandle.HandleValue, _leftSpeed, _rightSpeed);
}

void UFL_SteamInput::TriggerVibrationExtended(FInputHandle _inputHandle, int32 _leftSpeed, int32 _rightSpeed, int32 _leftTriggerSpeed, int32 _rightTriggerSpeed)
{
	SteamInput()->TriggerVibrationExtended(_inputHandle.HandleValue, _leftSpeed, _rightSpeed, _leftTriggerSpeed, _rightTriggerSpeed);
}

ECInputActionOrigin UFL_SteamInput::TranslateActionOrigin(ECSteamInputType _destinationInputType, ECInputActionOrigin _sourceOrigin)
{
	return ECInputActionOrigin(SteamInput()->TranslateActionOrigin(ESteamInputType(_destinationInputType), EInputActionOrigin(_sourceOrigin)));
}
