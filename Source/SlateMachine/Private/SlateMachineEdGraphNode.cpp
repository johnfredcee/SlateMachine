// Copyright (C) John Connors 2023

#include "SlateMachineEdGraphNode.h"

void USlateMachineEdGraphNode::AllocateDefaultPins()
{
}

FText USlateMachineEdGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromString(TEXT("Placeholder"));
}

TSharedPtr<SGraphNode> USlateMachineEdGraphNode::CreateVisualWidget()
{
    return TSharedPtr<SGraphNode>();
};
