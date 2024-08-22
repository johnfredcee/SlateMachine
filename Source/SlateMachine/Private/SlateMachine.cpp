// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlateMachine.h"
#include "SlateMachineStyle.h"
#include "SlateMachineCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

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

TSharedRef<SDockTab> FSlateMachineModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[

			    SNew(SSplitter)
			    .PhysicalSplitterHandleSize(10.0f)  
			    .Orientation(EOrientation::Orient_Horizontal)
                +SSplitter::Slot()
			    [
			        SNew(SBorder)
			        [
			            SNew(SBox)
                        .MinDesiredWidth(300.0f)
                        [
                            SNew(STextBlock)
                            .Justification(ETextJustify::Left)
                            .Text(LOCTEXT("DetailsPlaceholder", "Details Panel Goes Here"))
                        ]
			        ]
			    ]
			    +SSplitter::Slot()
			    [
			        SNew(SBorder)
			        [
			            SNew(SBox)
			            .MinDesiredWidth(600.0f)
                        [
                            SNew(STextBlock)
                            .Text(LOCTEXT("GraphPlaceholder", "Graph Goes Here"))
                        ]
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
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
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