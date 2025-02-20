// // Copyright (C) John Connors 2023

#include "SlateMachineSchema.h"
#include "SimpleStateMachine.h"
#include "SlateMachineEdGraph.h"
#include "SlateMachineEdGraphNode.h"

#define LOCTEXT_NAMESPACE "SlateMachineSchema"

UEdGraphNode* FSlateMachineSchemaAction_NewNode::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
    USlateMachineEdGraph* SlateMachineGraph = Cast<USlateMachineEdGraph>(ParentGraph);
    const USlateMachineSchema* Schema = CastChecked<USlateMachineSchema>(ParentGraph->GetSchema());

    USimpleStateMachine* StateMachine = SlateMachineGraph->StateMachine; 
    StateMachine->States.Emplace(FName("NewState"), { FName("NewState"), {}});
    FGraphNodeCreator<USlateMachineEdGraphNode> GraphNodeCreator(*SlateMachineGraph);
    USlateMachineEdGraphNode* Result = GraphNodeCreator.CreateNode(false, USlateMachineEdGraphNode::StaticClass());
    Result->OnRenameNode(TEXT("NewState"));    
    GraphNodeCreator.Finalize();
    Result->NodePosX = Location.X;
    Result->NodePosY = Location.Y;
    return Result;
}

void  USlateMachineSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const 
{

	const FText Name = LOCTEXT("NewStateNode", "New State Node");
	const FText ToolTip = LOCTEXT("NewSoundClassTooltip", "Create a new state node");
	
	TSharedPtr<FSlateMachineSchemaAction_NewNode> NewAction(new FSlateMachineSchemaAction_NewNode(FText::GetEmpty(), Name, ToolTip, 0));

	ContextMenuBuilder.AddAction( NewAction );

};

// void  USlateMachineSchema::GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const {


// };

FName USlateMachineSchema::GetParentContextMenuName() const 
{ 
    
    return NAME_None;

};

#undef LOCTEXT_NAMESPACE
