
#include "SSlateMachineGraphDetailsPanel.h"
#include "SSingleObjectDetailsPanel.h"

void SSlateMachineGraphDetailsPanel::Construct(const FArguments& InArgs, TWeakObjectPtr<USlateMachineEdGraph> InGraph)
{
    GraphDetails = InGraph;
    SSingleObjectDetailsPanel::Construct(SSingleObjectDetailsPanel::FArguments());
}

UObject *SSlateMachineGraphDetailsPanel::GetObjectToObserve() const
{
    return GraphDetails.Get();
}
