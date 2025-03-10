// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateMachine.h"
#include "EdGraph/EdGraphNode.h"
#include "GraphEditor.h"
#include "Logging/LogMacros.h"
#include "SSlateMachineGraphDetailsPanel.h"
#include "ScopedTransaction.h"
#include "SlateGlobals.h"
#include "SlateMachineEdGraph.h"
#include "SlateMachineEdGraphNode.h"
#include "SlateMachineStyle.h"
#include "SlateMachineCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

DEFINE_LOG_CATEGORY(LogSlateMachine)

static const FName SlateMachineTabName("SlateMachine");

#define LOCTEXT_NAMESPACE "FSlateMachineModule"

void FSlateMachineModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSlateMachineStyle::Initialize();
	FSlateMachineStyle::ReloadTextures();

	FSlateMachineCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSlateMachineCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSlateMachineModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FSlateMachineModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SlateMachineTabName, FOnSpawnTab::CreateRaw(this, &FSlateMachineModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FSlateMachineTabTitle", "SlateMachine"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

	SlateMachineGraph = NewObject<USlateMachineEdGraph>();
}

void FSlateMachineModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FSlateMachineStyle::Shutdown();

	FSlateMachineCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SlateMachineTabName);
}

void FSlateMachineModule::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{
	USlateMachineEdGraphNode* SlateMachineEdGraphNode = Cast<USlateMachineEdGraphNode>(NodeBeingChanged);
	if (SlateMachineEdGraphNode)
	{
		USlateMachineEdGraph* SlateMachineEdGraph = Cast<USlateMachineEdGraph>( SlateMachineEdGraphNode->GetGraph() );
		USimpleStateMachine* SlateMachine =  SlateMachineEdGraph->StateMachine;

		FString NodeTitle = SlateMachineEdGraphNode->GetNodeTitle(ENodeTitleType::EditableTitle).ToString();
		const FName StateName(NodeTitle);

		FSimpleState* StateToChange = SlateMachine->States.Find(StateName);
		if (ensure(StateToChange))
		{
			FName NewState(NewText.ToString());
			if (!SlateMachine->States.Contains(NewState))
			{
				SlateMachine->States.Remove(StateName);
				StateToChange->State = NewState;
				SlateMachine->States.Add(NewState, *StateToChange);
				const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "SlateMachineRenameNode", "Slate Machine: Rename Node"));
				SlateMachineEdGraphNode->Modify();
				SlateMachineEdGraphNode->OnRenameNode(*NewText.ToString());
			}	
		}
	};
}

bool FSlateMachineModule::OnVerifyNodeTitleCommit(const FText& NewText, UEdGraphNode* NodeBeingChanged, FText& OutErrorMessage)
{
	USlateMachineEdGraphNode* SlateMachineEdGraphNode = Cast<USlateMachineEdGraphNode>(NodeBeingChanged);
	if (SlateMachineEdGraphNode)
	{
		USlateMachineEdGraph* SlateMachineEdGraph = Cast<USlateMachineEdGraph>( SlateMachineEdGraphNode->GetGraph() );
		USimpleStateMachine* SlateMachine =  SlateMachineEdGraph->StateMachine;
		const FName StateName(NewText.ToString());
		FSimpleState* StateToChange = SlateMachine->States.Find(StateName);
		if (StateToChange)
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("StateName"), NewText);
			OutErrorMessage = FText::Format(LOCTEXT("StateExistsError", "{StateName} is an already existing state"), Arguments);
			return false;
		}
	}
	return true;
}

TSharedRef<SDockTab> FSlateMachineModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = LOCTEXT("AppearanceCornerText_SlateMachine", "SLATE MACHINE");
	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateRaw(this, &FSlateMachineModule::OnNodeTitleCommitted);
	InEvents.OnVerifyTextCommit = FOnNodeVerifyTextCommit::CreateRaw(this, &FSlateMachineModule::OnVerifyNodeTitleCommit);
	return	SNew(SDockTab)
			.TabRole(ETabRole::NomadTab)
			[
				SNew(SSplitter)
				.PhysicalSplitterHandleSize(10.0f)  
				.Orientation(EOrientation::Orient_Horizontal)
				+SSplitter::Slot()
				.Value(0.7f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
					[			        
						SNew(SGraphEditor)
						.GraphToEdit(SlateMachineGraph)
						.Appearance(AppearanceInfo)
						.GraphEvents(InEvents)
						.IsEditable(true)			
					]
				]
				+SSplitter::Slot()
				.Value(0.3f)
				[
					SNew(SBorder)
					.BorderImage(FAppStyle::GetBrush("ToolPanel.DarkGroupBorder"))
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.FillHeight(1.0f)
						[
							SAssignNew(GraphDetails, SSlateMachineGraphDetailsPanel, SlateMachineGraph)
							
						]
					]
				]
			];
}

void FSlateMachineModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(SlateMachineTabName);
}

void FSlateMachineModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("LevelEditor");
			Section.AddMenuEntryWithCommandList(FSlateMachineCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FSlateMachineCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSlateMachineModule, SlateMachine)