// // Copyright (C) John Connors 2023


#include "SlateMachineEdGraph.h"
#include "SimpleStateMachine.h"
#include "SlateMachineSchema.h"

#include "GraphEditAction.h"
#include "UObject/UObjectGlobals.h"

#define LOCTEXT_NAMESPACE "SlateMachineGraph"

DEFINE_LOG_CATEGORY_STATIC(LogSlateMachine, Verbose, All);

USlateMachineEdGraph::USlateMachineEdGraph() : Super()
{
    Schema = USlateMachineSchema::StaticClass();
    return;
}

void USlateMachineEdGraph::PostInitProperties()
{
    Super::PostInitProperties();
    StateMachine = NewObject<USimpleStateMachine>(this);
}

void USlateMachineEdGraph::AddNode(UEdGraphNode* NodeToAdd, bool bUserAction, bool bSelectNewNode)
{
    Super::AddNode(NodeToAdd, bUserAction, bSelectNewNode);
}

FString USlateMachineEdGraph::GetDesc()
{
    return TEXT("Slate Machine");
}

bool USlateMachineEdGraph::IsAsset() const
{
    return true;
}

bool USlateMachineEdGraph::IsEditorOnly() const
{
    return false;
}

void USlateMachineEdGraph::NotifyGraphChanged(const FEdGraphEditAction& Action)
{
    Super::NotifyGraphChanged(Action);
    UE_LOG(LogSlateMachine, Log, TEXT("%05x"), (int) Action.Action);
}

void USlateMachineEdGraph::RefreshGraph()
{
    return;
}
#undef LOCTEXT_NAMESPACE