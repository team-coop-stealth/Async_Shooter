// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputActionSetHandle.h"
#include "InputAnalogActionHandle.h"
#include "InputDigitalActionHandle.h"
#include "InputHandle.h"
#include "InputAnalogActionData.h"
#include "InputDigitalActionData.h"
#include "InputMotionData.h"
#include "FL_SteamInput.generated.h"

UENUM(BlueprintType)
/**
* Inputs the player binds to actions in the Steam Input Configurator.
* The chief purpose of these values is to direct which on-screen button glyphs should appear for a given action, such as "Press [A] to Jump".
*/
enum class ECInputActionOrigin : uint8
{
	None	                        UMETA(DisplayName = "None"),
	A                               UMETA(DisplayName = "(Valve Steam Controller) digital face button A"),
	B                               UMETA(DisplayName = "(Valve Steam Controller) digital face button B"),
	X                               UMETA(DisplayName = "(Valve Steam Controller) digital face button X"),
	Y                               UMETA(DisplayName = "(Valve Steam Controller) digital face button Y"),
	LeftBumper                      UMETA(DisplayName = "(Valve Steam Controller) digital left shoulder button (aka left bumper)"),
	RightBumper                     UMETA(DisplayName = "(Valve Steam Controller) digital right shoulder button (aka right bumper)"),
	LeftGrip                        UMETA(DisplayName = "(Valve Steam Controller) digital left grip paddle"),
	RightGrip                       UMETA(DisplayName = "(Valve Steam Controller) digital right grip paddle"),
	Start                           UMETA(DisplayName = "(Valve Steam Controller) digital start button"),
	Back                            UMETA(DisplayName = "(Valve Steam Controller) digital back button"),
	LeftPad_Touch                   UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, in simple contact with a finger"),
	LeftPad_Swipe                   UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, touch input on any axis"),
	LeftPad_Click                   UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, digital click (for the whole thing)"),
	LeftPad_DPadNorth               UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, digital click (upper quadrant)"),
	LeftPad_DPadSouth               UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, digital click (lower quadrant)"),
	LeftPad_DPadWest                UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, digital click (left quadrant)"),
	LeftPad_DPadEast                UMETA(DisplayName = "(Valve Steam Controller) left haptic touchpad, digital click (right quadrant)"),
	RightPad_Touch                  UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, in simple contact with a finger"),
	RightPad_Swipe                  UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, touch input on any axis"),
	RightPad_Click                  UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, digital click (for the whole thing)"),
	RightPad_DPadNorth              UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, digital click (upper quadrant)"),
	RightPad_DPadSouth              UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, digital click (lower quadrant)"),
	RightPad_DPadWest               UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, digital click (left quadrant)"),
	RightPad_DPadEast               UMETA(DisplayName = "(Valve Steam Controller) right haptic touchpad, digital click (right quadrant)"),
	LeftTrigger_Pull                UMETA(DisplayName = "(Valve Steam Controller) left analog trigger, pulled by any amount (analog value)"),
	LeftTrigger_Click               UMETA(DisplayName = "(Valve Steam Controller) left analog trigger, pulled in all the way (digital value)"),
	RightTrigger_Pull               UMETA(DisplayName = "(Valve Steam Controller) right analog trigger, pulled by any amount (analog value)"),
	RightTrigger_Click              UMETA(DisplayName = "(Valve Steam Controller) right analog trigger, pulled in all the way (digital value)"),
	LeftStick_Move                  UMETA(DisplayName = "(Valve Steam Controller) left joystick, movement on any axis (analog value)"),
	LeftStick_Click                 UMETA(DisplayName = "(Valve Steam Controller) left joystick, clicked in (digital value)"),
	LeftStick_DPadNorth             UMETA(DisplayName = "(Valve Steam Controller) left joystick, digital movement (upper quadrant)"),
	LeftStick_DPadSouth             UMETA(DisplayName = "(Valve Steam Controller) left joystick, digital movement (lower quadrant)"),
	LeftStick_DPadWest              UMETA(DisplayName = "(Valve Steam Controller) left joystick, digital movement (left quadrant)"),
	LeftStick_DPadEast              UMETA(DisplayName = "(Valve Steam Controller) left joystick, digital movement (right quadrant)"),
	Gyro_Move                       UMETA(DisplayName = "(Valve Steam Controller) gyroscope, analog movement in any axis"),
	Gyro_Pitch                      UMETA(DisplayName = "(Valve Steam Controller) gyroscope, analog movement on the Pitch axis (point head up to ceiling, point head down to floor)"),
	Gyro_Yaw                        UMETA(DisplayName = "(Valve Steam Controller) gyroscope, analog movement on the Yaw axis (turn head left to face one wall, turn head right to face other)"),
	Gyro_Roll                       UMETA(DisplayName = "(Valve Steam Controller) gyroscope, analog movement on the Roll axis (tilt head left towards shoulder, tilt head right towards other shoulder)"),
	SteamController_Reserved0       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved1       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved2       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved3       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved4       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved5       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved6       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved7       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved8       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved9       UMETA(DisplayName = "Reserved for future use"),
	SteamController_Reserved10      UMETA(DisplayName = "Reserved for future use"),
	PS4_X                           UMETA(DisplayName = "(Sony Dualshock 4) digital face button X"),
	PS4_Circle                      UMETA(DisplayName = "(Sony Dualshock 4) digital face button Circle"),
	PS4_Triangle                    UMETA(DisplayName = "(Sony Dualshock 4) digital face button Triangle"),
	PS4_Square                      UMETA(DisplayName = "(Sony Dualshock 4) digital face button Square"),
	PS4_LeftBumper                  UMETA(DisplayName = "(Sony Dualshock 4) digital left shoulder button (aka left bumper)"),
	PS4_RightBumper                 UMETA(DisplayName = "(Sony Dualshock 4) digital right shoulder button (aka right bumper)"),
	PS4_Options                     UMETA(DisplayName = "(Sony Dualshock 4) digital options button (aka Start)"),
	PS4_Share                       UMETA(DisplayName = "(Sony Dualshock 4) digital share button (aka Back)"),
	PS4_LeftPad_Touch               UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, in simple contact with a finger"),
	PS4_LeftPad_Swipe               UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, touch input on any axis"),
	PS4_LeftPad_Click               UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, digital click (for the whole thing)"),
	PS4_LeftPad_DPadNorth           UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, digital click (upper quadrant)"),
	PS4_LeftPad_DPadSouth           UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, digital click (lower quadrant)"),
	PS4_LeftPad_DPadWest            UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, digital click (left quadrant)"),
	PS4_LeftPad_DPadEast            UMETA(DisplayName = "(Sony Dualshock 4) left half of the touchpad, digital click (right quadrant)"),
	PS4_RightPad_Touch              UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, in simple contact with a finger"),
	PS4_RightPad_Swipe              UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, touch input on any axis"),
	PS4_RightPad_Click              UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, digital click (for the whole thing)"),
	PS4_RightPad_DPadNorth          UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, digital click (upper quadrant)"),
	PS4_RightPad_DPadSouth          UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, digital click (lower quadrant)"),
	PS4_RightPad_DPadWest           UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, digital click (left quadrant)"),
	PS4_RightPad_DPadEast           UMETA(DisplayName = "(Sony Dualshock 4) right half of the touchpad, digital click (right quadrant)"),
	PS4_CenterPad_Touch             UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, in simple contact with a finger"),
	PS4_CenterPad_Swipe             UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, touch input on any axis"),
	PS4_CenterPad_Click             UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, digital click (for the whole thing)"),
	PS4_CenterPad_DPadNorth         UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, digital click (upper quadrant)"),
	PS4_CenterPad_DPadSouth         UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, digital click (lower quadrant)"),
	PS4_CenterPad_DPadWest          UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, digital click (left quadrant)"),
	PS4_CenterPad_DPadEast          UMETA(DisplayName = "(Sony Dualshock 4) unified touchpad, digital click (right quadrant)"),
	PS4_LeftTrigger_Pull            UMETA(DisplayName = "(Sony Dualshock 4) left analog trigger, pulled by any amount (analog value)"),
	PS4_LeftTrigger_Click           UMETA(DisplayName = "(Sony Dualshock 4) left analog trigger, pulled in all the way (digital value)"),
	PS4_RightTrigger_Pull           UMETA(DisplayName = "(Sony Dualshock 4) right analog trigger, pulled by any amount (analog value)"),
	PS4_RightTrigger_Click          UMETA(DisplayName = "(Sony Dualshock 4) right analog trigger, pulled in all the way (digital value)"),
	PS4_LeftStick_Move              UMETA(DisplayName = "(Sony Dualshock 4) left joystick, movement on any axis (analog value)"),
	PS4_LeftStick_Click             UMETA(DisplayName = "(Sony Dualshock 4) left joystick, clicked in (digital value)"),
	PS4_LeftStick_DPadNorth         UMETA(DisplayName = "(Sony Dualshock 4) left joystick, digital movement (upper quadrant)"),
	PS4_LeftStick_DPadSouth         UMETA(DisplayName = "(Sony Dualshock 4) left joystick, digital movement (lower quadrant)"),
	PS4_LeftStick_DPadWest          UMETA(DisplayName = "(Sony Dualshock 4) left joystick, digital movement (left quadrant)"),
	PS4_LeftStick_DPadEast          UMETA(DisplayName = "(Sony Dualshock 4) left joystick, digital movement (right quadrant)"),
	PS4_RightStick_Move             UMETA(DisplayName = "(Sony Dualshock 4) right joystick, movement on any axis (analog value)"),
	PS4_RightStick_Click            UMETA(DisplayName = "(Sony Dualshock 4) right joystick, clicked in (digital value)"),
	PS4_RightStick_DPadNorth        UMETA(DisplayName = "(Sony Dualshock 4) right joystick, digital movement (upper quadrant)"),
	PS4_RightStick_DPadSouth        UMETA(DisplayName = "(Sony Dualshock 4) right joystick, digital movement (lower quadrant)"),
	PS4_RightStick_DPadWest         UMETA(DisplayName = "(Sony Dualshock 4) right joystick, digital movement (left quadrant)"),
	PS4_RightStick_DPadEast         UMETA(DisplayName = "(Sony Dualshock 4) right joystick, digital movement (right quadrant)"),
	PS4_DPad_North                  UMETA(DisplayName = "(Sony Dualshock 4) digital pad, pressed (upper quadrant)"),
	PS4_DPad_South                  UMETA(DisplayName = "(Sony Dualshock 4) digital pad, pressed (lower quadrant)"),
	PS4_DPad_West                   UMETA(DisplayName = "(Sony Dualshock 4) digital pad, pressed (left quadrant)"),
	PS4_DPad_East                   UMETA(DisplayName = "(Sony Dualshock 4) digital pad, pressed (right quadrant)"),
	PS4_Gyro_Move                   UMETA(DisplayName = "(Sony Dualshock 4) gyroscope, analog movement in any axis"),
	PS4_Gyro_Pitch                  UMETA(DisplayName = "(Sony Dualshock 4) gyroscope, analog movement on the Pitch axis (point head up to ceiling, point head down to floor)"),
	PS4_Gyro_Yaw                    UMETA(DisplayName = "(Sony Dualshock 4) gyroscope, analog movement on the Yaw axis (turn head left to face one wall, turn head right to face other)"),
	PS4_Gyro_Roll                   UMETA(DisplayName = "(Sony Dualshock 4) gyroscope, analog movement on the Roll axis (tilt head left towards shoulder, tilt head right towards other shoulder)"),
	PS4_Reserved0                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved1                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved2                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved3                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved4                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved5                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved6                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved7                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved8                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved9                   UMETA(DisplayName = "Reserved for future use"),
	PS4_Reserved10                  UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_A						UMETA(DisplayName = "(XB1)digital face button A"),
	XBoxOne_B						UMETA(DisplayName = "(XB1)digital face button B"),
	XBoxOne_X						UMETA(DisplayName = "(XB1)digital face button Cross"),
	XBoxOne_Y						UMETA(DisplayName = "(XB1)digital face button Y"),
	XBoxOne_LeftBumper				UMETA(DisplayName = "(XB1)digital left shoulder button (aka left bumper)"),
	XBoxOne_RightBumper				UMETA(DisplayName = "(XB1)digital right shoulder button (aka right bumper)"),
	XBoxOne_Menu					UMETA(DisplayName = "(XB1)digital menu button (aka start)"),
	XBoxOne_View					UMETA(DisplayName = "(XB1)digital view button (aka back)"),
	XBoxOne_LeftTrigger_Pull		UMETA(DisplayName = "(XB1)left analog trigger, pulled by any amount (analog value)"),
	XBoxOne_LeftTrigger_Click		UMETA(DisplayName = "(XB1)left analog trigger, pulled in all the way (digital value)"),
	XBoxOne_RightTrigger_Pull		UMETA(DisplayName = "(XB1)right analog trigger, pulled by any amount (analog value)"),
	XBoxOne_RightTrigger_Click		UMETA(DisplayName = "(XB1)right analog trigger, pulled in all the way (digital value)"),
	XBoxOne_LeftStick_Move			UMETA(DisplayName = "(XB1)left joystick, movement on any axis (analog value)"),
	XBoxOne_LeftStick_Click			UMETA(DisplayName = "(XB1)left joystick, clicked in (digital value)"),
	XBoxOne_LeftStick_DPadNorth		UMETA(DisplayName = "(XB1)left joystick, digital movement (upper quadrant)"),
	XBoxOne_LeftStick_DPadSouth		UMETA(DisplayName = "(XB1)left joystick, digital movement (lower quadrant)"),
	XBoxOne_LeftStick_DPadWest		UMETA(DisplayName = "(XB1)left joystick, digital movement (left quadrant)"),
	XBoxOne_LeftStick_DPadEast		UMETA(DisplayName = "(XB1)left joystick, digital movement (right quadrant)"),
	XBoxOne_RightStick_Move			UMETA(DisplayName = "(XB1)right joystick, movement on any axis (analog value)"),
	XBoxOne_RightStick_Click		UMETA(DisplayName = "(XB1)right joystick, clicked in (digital value)"),
	XBoxOne_RightStick_DPadNorth	UMETA(DisplayName = "(XB1)right joystick, digital movement (upper quadrant)"),
	XBoxOne_RightStick_DPadSouth	UMETA(DisplayName = "(XB1)right joystick, digital movement (lower quadrant)"),
	XBoxOne_RightStick_DPadWest		UMETA(DisplayName = "(XB1)right joystick, digital movement (left quadrant)"),
	XBoxOne_RightStick_DPadEast		UMETA(DisplayName = "(XB1)right joystick, digital movement (right quadrant)"),
	XBoxOne_DPad_North				UMETA(DisplayName = "(XB1)digital pad, pressed (upper quadrant)"),
	XBoxOne_DPad_South				UMETA(DisplayName = "(XB1)digital pad, pressed (lower quadrant)"),
	XBoxOne_DPad_West				UMETA(DisplayName = "(XB1)digital pad, pressed (left quadrant)"),
	XBoxOne_DPad_East				UMETA(DisplayName = "(XB1)digital pad, pressed (right quadrant)"),
	XBoxOne_Reserved0				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved1				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved2				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved3				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved4				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved5				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved6				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved7				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved8				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved9				UMETA(DisplayName = "Reserved for future use"),
	XBoxOne_Reserved10				UMETA(DisplayName = "Reserved for future use"),
	XBox360_A						UMETA(DisplayName = "(X360) digital face button A"),
	XBox360_B						UMETA(DisplayName = "(X360) digital face button B"),
	XBox360_X						UMETA(DisplayName = "(X360) digital face button X"),
	XBox360_Y						UMETA(DisplayName = "(X360) digital face button Y"),
	XBox360_LeftBumper				UMETA(DisplayName = "(X360) digital left shoulder button (aka left bumper)"),
	XBox360_RightBumper				UMETA(DisplayName = "(X360) digital right shoulder button (aka right bumper)"),
	XBox360_Start					UMETA(DisplayName = "(X360) digital start button"),
	XBox360_Back					UMETA(DisplayName = "(X360) digital back button"),
	XBox360_LeftTrigger_Pull		UMETA(DisplayName = "(X360) left analog trigger, pulled by any amount (analog value)"),
	XBox360_LeftTrigger_Click		UMETA(DisplayName = "(X360) left analog trigger, pulled in all the way (digital value)"),
	XBox360_RightTrigger_Pull		UMETA(DisplayName = "(X360) right analog trigger, pulled by any amount (analog value)"),
	XBox360_RightTrigger_Click		UMETA(DisplayName = "(X360) right analog trigger, pulled in all the way (digital value)"),
	XBox360_LeftStick_Move			UMETA(DisplayName = "(X360) left joystick, movement on any axis (analog value)"),
	XBox360_LeftStick_Click			UMETA(DisplayName = "(X360) left joystick, clicked in (digital value)"),
	XBox360_LeftStick_DPadNorth		UMETA(DisplayName = "(X360) left joystick, digital movement (upper quadrant)"),
	XBox360_LeftStick_DPadSouth		UMETA(DisplayName = "(X360) left joystick, digital movement (lower quadrant)"),
	XBox360_LeftStick_DPadWest		UMETA(DisplayName = "(X360) left joystick, digital movement (left quadrant)"),
	XBox360_LeftStick_DPadEast		UMETA(DisplayName = "(X360) left joystick, digital movement (right quadrant)"),
	XBox360_RightStick_Move			UMETA(DisplayName = "(X360) right joystick, movement on any axis (analog value)"),
	XBox360_RightStick_Click		UMETA(DisplayName = "(X360) right joystick, clicked in (digital value)"),
	XBox360_RightStick_DPadNorth	UMETA(DisplayName = "(X360) right joystick, digital movement (upper quadrant)"),
	XBox360_RightStick_DPadSouth	UMETA(DisplayName = "(X360) right joystick, digital movement (lower quadrant)"),
	XBox360_RightStick_DPadWest		UMETA(DisplayName = "(X360) right joystick, digital movement (left quadrant)"),
	XBox360_RightStick_DPadEast		UMETA(DisplayName = "(X360) right joystick, digital movement (right quadrant)"),
	XBox360_DPad_North				UMETA(DisplayName = "(X360) digital pad, pressed (upper quadrant)"),
	XBox360_DPad_South				UMETA(DisplayName = "(X360) digital pad, pressed (lower quadrant)"),
	XBox360_DPad_West				UMETA(DisplayName = "(X360) digital pad, pressed (left quadrant)"),
	XBox360_DPad_East				UMETA(DisplayName = "(X360) digital pad, pressed (right quadrant)"),
	XBox360_Reserved0				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved1				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved2				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved3				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved4				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved5				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved6				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved7				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved8				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved9				UMETA(DisplayName = "Reserved for future use"),
	XBox360_Reserved10				UMETA(DisplayName = "Reserved for future use"),
	Switch_A						UMETA(DisplayName = "(Nintendo Switch Pro) digital face button A"),
	Switch_B						UMETA(DisplayName = "(Nintendo Switch Pro) digital face button B"),
	Switch_X						UMETA(DisplayName = "(Nintendo Switch Pro) digital face button X"),
	Switch_Y						UMETA(DisplayName = "(Nintendo Switch Pro) digital face button Y"),
	Switch_LeftBumper				UMETA(DisplayName = "(Nintendo Switch Pro) digital left shoulder button (aka left bumper)"),
	Switch_RightBumper				UMETA(DisplayName = "(Nintendo Switch Pro) digital right shoulder button (aka right bumper)"),
	Switch_Plus						UMETA(DisplayName = "(Nintendo Switch Pro) plus button"),
	Switch_Minus					UMETA(DisplayName = "(Nintendo Switch Pro) minus button"),
	Switch_Capture					UMETA(DisplayName = "(Nintendo Switch Pro) digital capture button"),
	Switch_LeftTrigger_Pull			UMETA(DisplayName = "(Nintendo Switch Pro) left trigger, clicked"),
	Switch_LeftTrigger_Click		UMETA(DisplayName = "(Nintendo Switch Pro) left trigger, clicked (same as previous value)"),
	Switch_RightTrigger_Pull		UMETA(DisplayName = "(Nintendo Switch Pro) right trigger, clicked"),
	Switch_RightTrigger_Click		UMETA(DisplayName = "(Nintendo Switch Pro) right trigger, clicked (same as previous value)"),
	Switch_LeftStick_Move			UMETA(DisplayName = "(Nintendo Switch Pro) left joystick, movement on any axis (analog value)"),
	Switch_LeftStick_Click			UMETA(DisplayName = "(Nintendo Switch Pro) left joystick, clicked in (digital value)"),
	Switch_LeftStick_DPadNorth		UMETA(DisplayName = "(Nintendo Switch Pro) left joystick, digital movement (upper quadrant)"),
	Switch_LeftStick_DPadSouth		UMETA(DisplayName = "(Nintendo Switch Pro) left joystick, digital movement (lower quadrant)"),
	Switch_LeftStick_DPadWest		UMETA(DisplayName = "(Nintendo Switch Pro) left joystick, digital movement (left quadrant)"),
	Switch_LeftStick_DPadEast		UMETA(DisplayName = "(Nintendo Switch Pro) left joystick, digital movement (right quadrant)"),
	Switch_RightStick_Move			UMETA(DisplayName = "(Nintendo Switch Pro) right joystick, movement on any axis (analog value)"),
	Switch_RightStick_Click			UMETA(DisplayName = "(Nintendo Switch Pro) right joystick, clicked in (digital value)"),
	Switch_RightStick_DPadNorth		UMETA(DisplayName = "(Nintendo Switch Pro) right joystick, digital movement (upper quadrant)"),
	Switch_RightStick_DPadSouth		UMETA(DisplayName = "(Nintendo Switch Pro) right joystick, digital movement (lower quadrant)"),
	Switch_RightStick_DPadWest		UMETA(DisplayName = "(Nintendo Switch Pro) right joystick, digital movement (left quadrant)"),
	Switch_RightStick_DPadEast		UMETA(DisplayName = "(Nintendo Switch Pro) right joystick, digital movement (right quadrant)"),
	Switch_DPad_North				UMETA(DisplayName = "(Nintendo Switch Pro) digital pad, pressed (upper quadrant)"),
	Switch_DPad_South				UMETA(DisplayName = "(Nintendo Switch Pro) digital pad, pressed (lower quadrant)"),
	Switch_DPad_West				UMETA(DisplayName = "(Nintendo Switch Pro) digital pad, pressed (left quadrant)"),
	Switch_DPad_East				UMETA(DisplayName = "(Nintendo Switch Pro) digital pad, pressed (right quadrant)"),
	SwitchProGyro_Move				UMETA(DisplayName = "(Nintendo Switch Pro) gyroscope, analog movement in any axis"),
	SwitchProGyro_Pitch				UMETA(DisplayName = "(Nintendo Switch Pro) gyroscope, analog movement on the Pitch axis (point head up to ceiling, point head down to floor)"),
	SwitchProGyro_Yaw				UMETA(DisplayName = "(Nintendo Switch Pro) gyroscope, analog movement on the Yaw axis (turn head left to face one wall, turn head right to face other)"),
	SwitchProGyro_Roll				UMETA(DisplayName = "(Nintendo Switch Pro) gyroscope, analog movement on the Roll axis (tilt head left towards shoulder, tilt head right towards other shoulder)"),
	Switch_Reserved0				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved1				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved2				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved3				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved4				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved5				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved6				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved7				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved8				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved9				UMETA(DisplayName = "Reserved for future use"),
	Switch_Reserved10				UMETA(DisplayName = "Reserved for future use"),
};

UENUM(BlueprintType)
/**
* A region of the controller that can be thought of as a larger abstract modular unit that one of many modes can be applied to and output meaningful data.
* For example, a joystick can be treated as either a single analog input, or broken up into four discrete digital forming a virtual DPAD.
* Likewise, the ABXY face buttons form a natural group that be treated as four independent buttons, or as components of a virtual DPAD, etc.
*/
enum class ECInputSource : uint8 {
	None = 0		UMETA(DisplayName = "No controller source."),
	LeftTrackpad	UMETA(DisplayName = "The left touchpad, or the left half of a central touchpad."),
	RightTrackpad	UMETA(DisplayName = "The right touchpad, or the right half of a central touchpad."),
	Joystick		UMETA(DisplayName = "The joystick, or if there is more than one joystick, the left joystick."),
	ABXY			UMETA(DisplayName = "The four main face buttons."),
	Switch			UMETA(DisplayName = "Switches / buttons on the controller that don't belong to any other specific source. This includes bumpers, start/select, and grips. This special case of misfits don't fit into the larger paradigm and thus get their own source of digital buttons and a corresponding mode that processes them."),
	LeftTrigger		UMETA(DisplayName = "The left analog trigger."),
	RightTrigger	UMETA(DisplayName = "The right analog trigger."),
	Gyro			UMETA(DisplayName = "The internal gyroscope."),
	CenterTrackpad	UMETA(DisplayName = "The central touchpad. (DS4 only)"),
	RightJoystick	UMETA(DisplayName = "The right joystick.If there is only one joystick, this source is not used."),
	DPad			UMETA(DisplayName = "The digital pad."),
	Key				UMETA(DisplayName = "Keyboard key(for keyboards with scan codes)."),
	Mouse			UMETA(DisplayName = "Traditional mouse"),
	Count			UMETA(DisplayName = "The number of enums, useful for iterating.")
};

UENUM(BlueprintType)
/**
* Controls the color of a Steam Controller Device's LED (if the device indeed has one).
*/
enum class ECSteamControllerLEDFlag : uint8 {
	SetColor			UMETA(DisplayName = "Set the color to the specified values"),
	RestoreUserDefault	UMETA(DisplayName = "Restore the color to default (out - of - game) settings")
};

UENUM(BlueprintType)
/**
* These values are passed into GetGlyphPNGForActionOrigin
*/
enum class ECSteamInputGlyphSize : uint8
{
	k_ESteamInputGlyphSize_Small	UMETA(DisplayName = "Small (32x32px)"),
	k_ESteamInputGlyphSize_Medium	UMETA(DisplayName = "Medium (128x128px)"),
	k_ESteamInputGlyphSize_Large	UMETA(DisplayName = "Large (256x256px)"),
	k_ESteamInputGlyphSize_Count	UMETA(DisplayName = "Count")
};

UENUM(BlueprintType)
enum class ECControllerHapticLocation : uint8
{
	None,
	Left = k_EControllerHapticLocation_Left		UMETA(DisplayName = "Left"),
	Right = k_EControllerHapticLocation_Right	UMETA(DisplayName = "Right"),
	Both = k_EControllerHapticLocation_Both		UMETA(DisplayName = "Both"),
};

UENUM(BlueprintType)
/**
* Represents the device model for a given piece of hardware.
*/
enum class ECSteamInputType : uint8 {
	Unknown = 0			UMETA(DisplayName = "Catch - all for unrecognized devices"),
	SteamController		UMETA(DisplayName = "Valve's Steam Controller"),
	XBox360Controller	UMETA(DisplayName = "Microsoft's XBox 360 Controller"),
	XBoxOneController	UMETA(DisplayName = "Microsoft's XBox One Controller"),
	GenericXInput		UMETA(DisplayName = "Any generic 3rd - party XInput device"),
	PS4Controller		UMETA(DisplayName = "Sony's PlayStation 4 Controller"),
	AppleMFiController	UMETA(DisplayName = "Apple MFi Controller - Unused"),
	AndroidController	UMETA(DisplayName = "Android Controller - Unused"),
	SwitchJoyConPair	UMETA(DisplayName = "Switch JoyCon Pair - Unused"),
	SwitchJoyConSingle	UMETA(DisplayName = "Switch JoyCon Single - Unused"),
	SwitchProController	UMETA(DisplayName = "Nintendo's Switch Pro Controller"),
	MobileTouch			UMETA(DisplayName = "Steam Link App's Mobile Touch Controller"),
	PS3Controller		UMETA(DisplayName = "Sony's PlayStation 3 Controller or PS3/PS4 compatible fight stick"),
	Count				UMETA(DisplayName = "Current number of values returned"),
	MaximumPossibleValue = 255	UMETA(DisplayName = "Maximum possible value returned")
};

UENUM(BlueprintType)
/**
* A touchpad region on a Steam Controller Device.
*/
enum class ECSteamControllerPad : uint8 {
	Left = 0	UMETA(DisplayName = "The left touchpad region on a Steam Controller Device.Compatible models : VSC, DS4"),
	Right		UMETA(DisplayName = "The right region on a Steam Controller Device.Compatible models : VSC, DS4")
};

/**
 * 
 */
UCLASS()
class ASYNC_SHOOTER_API UFL_SteamInput : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Reconfigure the controller to use the specified action set (i.e. "Menu", "Walk", or "Drive").
	* This is cheap, and can be safely called repeatedly. It's often easier to repeatedly call it in your state loops, instead of trying to place it in all of your state transitions.
	* @param FInputHandle	The handle of the controller you want to activate an action set for.
	* @param FInputActionSetHandle	The handle of the action set you want to activate.
	*/
	static void ActivateActionSet(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Reconfigure the controller to use the specified action set layer.
	* See the Action Set Layers article for full details and an in-depth practical example.
	* https://partner.steamgames.com/doc/features/steam_controller/action_set_layers
	* @param FInputHandle	The handle of the controller you want to deactivate an action set layer for.
	* @param FInputActionSetHandle	The handle of the action set layer you want to deactivate.
	*/
	static void ActivateActionSetLayer(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Reconfigure the controller to stop using the specified action set layer.
	* @param FInputHandle	The handle of the controller you want to deactivate an action set layer for.
	* @param FInputActionSetHandle	The handle of the action set layer you want to deactivate.
	*/
	static void DeactivateActionSetLayer(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Reconfigure the controller to stop using all action set layers.
	* @param FInputHandle	The handle of the controller you want to deactivate all action set layers for.
	*/
	static void DeactivateAllActionSetLayers(FInputHandle _inputHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Fill an array with all of the currently active action set layers for a specified controller handle.
	* @param UInputHandle	The handle of the controller you want to get active action set layers for.
	* @param TArray<FInputActionSetHandle>	This must point to a STEAM_INPUT_MAX_COUNT sized array of FInputActionSetHandle.
	* @return Array of FInputActionSetHandle
	*/
	static TArray<FInputActionSetHandle> GetActiveActionSetLayers(FInputHandle _inputHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Lookup the handle for an Action Set. Best to do this once on startup, and store the handles for all future API calls.
	* @param FString	The string identifier of an action set defined in the game's VDF file.
	* @return The handle of the specified action set.
	*/
	static FInputActionSetHandle GetActionSetHandle(FString _actionSetName);
	
	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns the current state of the supplied analog game action.
	*/
	static FInputAnalogActionData GetAnalogActionData(FInputHandle _inputHandle, FInputAnalogActionHandle _inputAnalogActionHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get the handle of the specified Analog action.
	* NOTE: This function does not take an action set handle parameter. 
	* That means that each action in your VDF file must have a unique string identifier. 
	* In other words, if you use an action called "up" in two different action sets, this function will only ever return one of them and the other will be ignored.
	* &param FString	The string identifier of the analog action defined in the game's VDF file.
	* @return The handle of the specified analog action.
	*/
	static FInputAnalogActionHandle GetAnalogActionHandle(FString _actionName);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get the origin(s) for an analog action within an action set by filling originsOut with EInputActionOrigin handles. 
	* Use this to display the appropriate on-screen prompt for the action.
	* @param FInputHandle	The handle of the controller you want to query.
	* @param FInputActionSetHandle	The handle of the action set you want to query.
	* @param FInputAnalogActionHandle	The handle of the analog action you want to query.
	* @return Array of UEInputActionOrigin handles.
	*/
	static TArray<ECInputActionOrigin> GetAnalogActionOrigins(FInputHandle _inputHandle, FInputActionSetHandle _inputActionSetHandle, FInputAnalogActionHandle _inputAnalogActionHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Enumerates currently connected controllers returning with the currently connected controller handles.
	* @return array of FInputHandle.
	*/
	static TArray<FInputHandle> GetConnectedControllers();

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns the associated controller handle for the specified emulated gamepad. 
	* Can be used with GetInputTypeForHandle to determine the type of controller using Steam Input Gamepad Emulation.
	* @param int32	The index of the emulated gamepad you want to get a controller handle for.
	* @return Controller handle
	*/
	static FInputHandle GetControllerForGamepadIndex(int32 _index);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get the currently active action set for the specified controller.
	* @param FInputHandle	The handle of the controller you want to query.
	* @return The handle of the action set activated for the specified controller.
	*/
	static FInputActionSetHandle GetCurrentActionSet(FInputHandle _inputHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns the current state of the supplied digital game action.
	* &param FInputHandle	The handle of the controller you want to query.
	* &param FInputDigitalActionHandle	The handle of the digital action you want to query.
	* @return The current state of the specified digital action.
	*/
	static FInputDigitalActionData GetDigitalActionData(FInputHandle _inputHandle, FInputDigitalActionHandle _digitalActionHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get the handle of the specified digital action.
	* NOTE: This function does not take an action set handle parameter. 
	* That means that each action in your VDF file must have a unique string identifier. 
	* In other words, if you use an action called "up" in two different action sets, 
	* this function will only ever return one of them and the other will be ignored.
	* @param FString	The string identifier of the digital action defined in the game's VDF file.
	* @return The handle of the specified digital action.
	*/
	static FInputDigitalActionHandle GetDigitalActionHandle(FString _actionName);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get the origin(s) for a digital action within an action set by returning UEInputActionOrigin handles. 
	* Use this to display the appropriate on-screen prompt for the action.
	* @param FInputHandle	The handle of the controller you want to query.
	* @param FInputActionSetHandle	The handle of the action set you want to query.
	* @param FInputDigitalActionHandle	The handle of the digital action you want to query.
	* @return Array of ECInputActionOrigin handles
	*/
	static TArray<ECInputActionOrigin> GetDigitalActionOrigins(FInputHandle _inputHandle, FInputActionSetHandle _actionSetHandle, FInputDigitalActionHandle _digitalActionHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns the associated gamepad index for the specified controller, if emulating a gamepad.
	* @param FInputHandle	The handle of the controller you want to get a gamepad index for.
	*/
	static int32 GetGamepadIndexForController(FInputHandle _controllerHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get a local path to art for on-screen glyph for a particular origin.
	* @param ECInputActionOrigin Action Origin, which you want to query
	* @param ECSteamInputGlyphSize The size of the glyph.
	* @param Flags
	* @return The path to the png file for the glyph.
	* E.g. "C:\Program Files (x86)\Steam\tenfoot\resource\images\library\controller\api\ps4_button_x.png"
	*/
	static FString GetGlyphPNGForActionOrigin(ECInputActionOrigin _origin, ECSteamInputGlyphSize _glyphSize, int32 _flags);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Get a local path to art for on-screen glyph for a particular origin.
	* @param ECInputActionOrigin Action Origin, which you want to query
	* @param Flags
	* @return The path to the svg file for the glyph.
	* E.g. "C:\Program Files (x86)\Steam\tenfoot\resource\images\library\controller\api\ps4_button_x.png"
	*/
	static FString GetGlyphSVGForActionOrigin(ECInputActionOrigin _origin, int32 _flags);


	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns the input type (device model) for the specified controller. 
	* This tells you if a given controller is a Steam controller, Xbox 360 controller, PS4 controller, etc.
	* @param FInputHandle	The handle of the controller whose input type (device model) you want to query
	* @return The input type of the controller
	*/
	static ECSteamInputType GetInputTypeForHandle(FInputHandle _inputHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns raw motion data for the specified controller.
	* @param FInputHandle	The handle of the controller you want to get motion data for.
	* @return Raw motion data
	*/
	static FInputMotionData GetMotionData(FInputHandle _inputHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Returns a localized string (from Steam's language setting) for the specified origin.
	* @param UEInputActionOrigin	Action Origin, which you want to query
	* @return String of the origin
	*/
	static FString GetStringForActionOrigin(ECInputActionOrigin _origin);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Must be called when starting use of the ISteamInput interface.
	* @return Always returns true
	*/
	static bool Init();

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Synchronize API state with the latest Steam Controller inputs available. 
	* This is performed automatically by SteamAPI_RunCallbacks, 
	* but for the absolute lowest possible latency, you can call this directly before reading controller state.
	*/
	static void RunFrame();

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Set the controller LED color on supported controllers.
	* Notes:
	* The VSC does not support any color but white, and will interpret the RGB values as a greyscale value affecting the brightness of the Steam button LED.
	* The DS4 responds to full color information and uses the values to set the color & brightness of the lightbar.
	* @param FInputHandle	The handle of the controller to affect.
	* @param FColor	Color to be set.
	* @param ECSteamControllerLEDFlag	Bit-masked flags combined from values defined in ESteamControllerLEDFlag.
	*/
	static void SetLEDColor(FInputHandle _inputHandle, FColor _color, ECSteamControllerLEDFlag _flags);
	
	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Invokes the Steam overlay and brings up the binding screen.
	* @return true for success; false if overlay is disabled/unavailable. 
	* If the player is using Big Picture Mode the configuration will open in the overlay. 
	* In desktop mode a popup window version of Big Picture will be created and open the configuration.
	*/
	static bool ShowBindingPanel(FInputHandle _inputHandle);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Must be called when ending use of the ISteamInput interface.
	* @return Always returns true.
	*/
	static bool Shutdown();

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Stops the momentum of an analog action (where applicable, i.e. a touchpad w/ virtual trackball settings).
	* NOTE:
	* This will also stop all associated haptics. 
	* This is useful for situations where you want to indicate to the user that the limit of an action has been reached, 
	* such as spinning a carousel or scrolling a webpage.
	* @param FInputHandle	The handle of the controller to affect.
	* @param FInputAnalogActionHandle	The analog action to stop momentum for.
	*/
	static void StopAnalogActionMomentum(FInputHandle _inputHandle, FInputAnalogActionHandle _action);

	// Send a haptic pulse, works on Steam Deck and Steam Controller devices
	static void TriggerSimpleHapticEvent(FInputHandle _inputHandle, ECControllerHapticLocation _hapticLocation, int32 _intensity, char _gainDB, int32 _otherIntensity, char _otherGainDB);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Triggers a (low-level) haptic pulse on supported controllers.
	* Notes:
	* Currently only the VSC supports haptic pulses.
	* This API call will be ignored for all other controller models.
	* The typical max value of an unsigned short is 65535, which means the longest haptic pulse you can trigger with this method has a duration of 0.065535 seconds (ie, less than 1/10th of a second). 
	* This function should be thought of as a low-level primitive meant to be repeatedly used in higher-level user functions to generate more sophisticated behavior.
	* @param FInputHandle	The handle of the controller to affect.
	* @param ECSteamControllerPad	Which haptic touchpad to affect.
	* @param int32	Duration of the pulse, in microseconds (1/1,000,000th of a second)
	*/
	static void Legacy_TriggerHapticPulse(FInputHandle _inputHandle, ECSteamControllerPad _targetPad, int32 _durationMicroSec);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Triggers a repeated haptic pulse on supported controllers.
	* Notes:
	* Currently only the Steam Controller, Steam Deck, and Nintendo Switch Pro Controller devices support haptic pulses.
	* This API call will be ignored for incompatible controller models.
	* This is a more user-friendly function to call than TriggerHapticPulse as it can generate pulse patterns long enough to be actually noticed by the user.
	* Changing the DurationMicroSec and OffMicroSec parameters will change the "texture" of the haptic pulse.
	* @param FInputHandle	The handle of the controller to affect.
	* @param ECSteamControllerPad	Which haptic touchpad to affect.
	* @param int32	Duration of the pulse, in microseconds (1/1,000,000th of a second).
	* @param int32	Duration of the pause between pulses, in microseconds.
	* @param int32	Number of times to repeat the DurationMicroSec / OffMicroSec duty cycle.
	* @param int32	Currently unused.
	*/
	static void Legacy_TriggerRepeatedHapticPulse(FInputHandle _inputHandle, ECSteamControllerPad _targetPad, int32 _durationMicroSec, int32 _offMicroSec, int32 _repeat, int32 _flags);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Trigger a vibration event on supported controllers.
	* Notes:
	* This API call will be ignored for incompatible controller models.
	* This generates the traditional "rumble" vibration effect.
	* The VSC will emulate traditional rumble using its haptics.
	* @param FInputHandle	The handle of the controller to affect.
	* @param int32	The intensity value for the left rumble motor.
	* @param int32	The intensity value of the right rumble motor.
	*/
	static void TriggerVibration(FInputHandle _inputHandle, int32 _leftSpeed, int32 _rightSpeed);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/**
	* Trigger a vibration event on supported controllers, including Xbox Impulse Trigger motor values.
	* Notes:
	* On Windows support for Xbox Impulse Trigger motor values requires user installation of the Xbox Extended Feature support driver.
	* The Steam Controller and Steam Deck will emulate traditional rumble using their haptics.
	* @param FInputHandle	The handle of the controller to affect.
	* @param int32	The intensity value for the left rumble motor.
	* @param int32	The intensity value of the right rumble motor.
	* @param int32	The intensity value for the left Xbox Impulse Trigger motor.
	* @param int32	The intensity value of the right Xbox Impulse Trigger motor.
	*/
	static void TriggerVibrationExtended(FInputHandle _inputHandle, int32 _leftSpeed, int32 _rightSpeed, int32 _leftTriggerSpeed, int32 _rightTriggerSpeed);

	UFUNCTION(BlueprintCallable, Category = "Steamworks|SteamInput")
	/*
	* Get the equivalent origin for a given controller type or the closest controller type that existed in the SDK you built into your game 
	* if eDestinationInputType is k_ESteamInputType_Unknown. 
	* This action origin can be used in your glyph look up table or passed into GetGlyphForActionOrigin or GetStringForActionOrigin.
	* @return ECInputActionOrigin
	*/
	static ECInputActionOrigin TranslateActionOrigin(ECSteamInputType _destinationInputType, ECInputActionOrigin _sourceOrigin);
};

