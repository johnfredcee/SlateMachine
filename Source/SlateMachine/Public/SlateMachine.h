// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GraphEditor.h"
#include "Logging/LogMacros.h"
#include "Logging/LogVerbosity.h"
#include "Modules/ModuleManager.h"
#include "SlateMachineEdGraph.h"

class FToolBarBuilder;
class FMenuBuilder;

DECLARE_LOG_CATEGORY_EXTERN(LogSlateMachine, Verbose, All);

class FSlateMachineModule : public IModuleInterface, public TSharedFromThis<FSlateMachineModule>
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	// the actual graph representing the state machine
	TObjectPtr<USlateMachineEdGraph> SlateMachineGraph; 

	// Top level graph editor widget
	TSharedPtr<SGraphEditor> GraphEditor;

	TSharedPtr<class FUICommandList> PluginCommands;

	// Add memnu items to the Level Editor toolbar
	void RegisterMenus();

	// called when we want to spawn a tabbed window with the graph inside
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	/**
	 * Called when a node's title is committed for a rename
	 */
	 void OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged);
	 bool OnVerifyNodeTitleCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage);

};
