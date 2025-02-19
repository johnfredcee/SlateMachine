//  Copyright (C) John Connors 2023

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"

#include "SlateMachineEdGraphNode.generated.h"

/**
 * Editor Node Object that represents a state machine state
 */
UCLASS()
class SLATEMACHINE_API USlateMachineEdGraphNode : public UEdGraphNode
{
    GENERATED_UCLASS_BODY()
public:
    virtual void AllocateDefaultPins() override;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual TSharedPtr<SGraphNode> CreateVisualWidget();
    void SetStateName(FName InName);
private:
    FName StateName;
};
