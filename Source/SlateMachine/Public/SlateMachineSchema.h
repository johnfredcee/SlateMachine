// // Copyright (C) John Connors 2023

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "K2Node.h"
#include "SlateMachineSchema.generated.h"

/**
 * 
 */
UCLASS()
class SLATEMACHINE_API USlateMachineSchema : public UEdGraphSchema
{
    GENERATED_BODY()

    virtual EGraphType GetGraphType(const UEdGraph* TestEdGraph) const override
    {
        return GT_StateMachine;
    }
};
