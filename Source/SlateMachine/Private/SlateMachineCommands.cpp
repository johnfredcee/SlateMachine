// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateMachineCommands.h"

#define LOCTEXT_NAMESPACE "FSlateMachineModule"

void FSlateMachineCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SlateMachine", "Bring up SlateMachine window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
