// // Copyright (C) John Connors 2023

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Internationalization.h"
#include "EdGraph/EdGraphSchema.h"
#include "K2Node.h"
#include "SlateMachineSchema.generated.h"

USTRUCT()
struct  FSlateMachineSchemaAction_NewNode : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();

	// Simple type info
	static FName StaticGetTypeId() {static FName Type("FSlateMachineSchemaAction_NewNode"); return Type;}

	FSlateMachineSchemaAction_NewNode() 
		: FEdGraphSchemaAction()
		, NewStateName(TEXT("StateName"))
	{}

	FSlateMachineSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(MoveTemp(InNodeCategory), MoveTemp(InMenuDesc), MoveTemp(InToolTip), InGrouping)
		, NewStateName(TEXT("StateName"))
	{}

	//~ Begin FEdGraphSchemaAction Interface
	virtual FName GetTypeId() const override { return StaticGetTypeId(); } 
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
	//~ End FEdGraphSchemaAction Interface

	/** Name for the new State */
	FString NewStateName;
};

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
    
    virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	//virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	virtual FName GetParentContextMenuName() const override;
	
};
