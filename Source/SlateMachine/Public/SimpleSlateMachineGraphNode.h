// Copyright (C) John Connors 2025

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "SGraphNode.h"
#include "SlateMachineEdGraphNode.h"

class SSimpleStateGraphNode : public SGraphNode
{
public:
    SLATE_BEGIN_ARGS(SSimpleStateGraphNode) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, USlateMachineEdGraphNode* InNode);
};