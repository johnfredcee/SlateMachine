// // Copyright (C) John Connors 2023

#pragma once

#include "CoreMinimal.h"
#include "SimpleStateMachine.h"
#include "EdGraph/EdGraph.h"
#include "SlateMachineEdGraph.generated.h"

/**
 * 
 */
UCLASS()
class SLATEMACHINE_API USlateMachineEdGraph : public UEdGraph
{
    GENERATED_BODY()

    UPROPERTY()
    TObjectPtr<USimpleStateMachine> StateMachine;
    
public:
    USlateMachineEdGraph();
    virtual void PostInitProperties() override;
    virtual void AddNode(UEdGraphNode* NodeToAdd, bool bUserAction, bool bSelectNewNode) override;
    virtual FString GetDesc() override;
    virtual bool IsAsset() const override;
    virtual bool IsEditorOnly() const override;
    virtual void NotifyGraphChanged(const FEdGraphEditAction& Action) override;

private:
    void RefreshGraph();
};
