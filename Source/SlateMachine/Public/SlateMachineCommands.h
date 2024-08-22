// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SlateMachineStyle.h"

class FSlateMachineCommands : public TCommands<FSlateMachineCommands>
{
public:

	FSlateMachineCommands()
		: TCommands<FSlateMachineCommands>(TEXT("SlateMachine"), NSLOCTEXT("Contexts", "SlateMachine", "SlateMachine Plugin"), NAME_None, FSlateMachineStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};