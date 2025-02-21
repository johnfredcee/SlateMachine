#pragma once

#include "SSingleObjectDetailsPanel.h"
#include "SlateMachineEdGraph.h"
#include "UObject/WeakObjectPtrTemplates.h"

class SSlateMachineGraphDetailsPanel : public SSingleObjectDetailsPanel
{
public:
	SLATE_BEGIN_ARGS(SSlateMachineGraphDetailsPanel) {}
	SLATE_END_ARGS()

    void Construct(const FArguments& InArgs, TWeakObjectPtr<USlateMachineEdGraph> InGraph);
    virtual UObject* GetObjectToObserve() const override;
private:
    TWeakObjectPtr<USlateMachineEdGraph> GraphDetails;
};
