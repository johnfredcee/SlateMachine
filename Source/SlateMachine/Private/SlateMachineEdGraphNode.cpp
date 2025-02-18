// Copyright (C) John Connors 2023

#include "SlateMachineEdGraphNode.h"
#include "SimpleSlateMachineGraphNode.h"

void USlateMachineEdGraphNode::AllocateDefaultPins()
{
   // Create an input pin for incoming state transitions
   CreatePin(EGPD_Input, TEXT("TransitionPin"), TEXT("In"));

   // Create an output pin for outgoing state transitions
   CreatePin(EGPD_Output, TEXT("TransitionPin"), TEXT("Out"));    
}

FText USlateMachineEdGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromName(StateName);
}

TSharedPtr<SGraphNode> USlateMachineEdGraphNode::CreateVisualWidget()
{
    return SNew(SSimpleStateGraphNode, this)
    .Visibility(EVisibility::Visible);

};

void USlateMachineEdGraphNode::SetStateName(FName InName)
{
    StateName = InName;
}
