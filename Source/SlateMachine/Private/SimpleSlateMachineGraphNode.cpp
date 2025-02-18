#include "SimpleSlateMachineGraphNode.h"
#include "SlateMachineEdGraphNode.h"

void SSimpleStateGraphNode::Construct(const FArguments& InArgs, USlateMachineEdGraphNode* InNode)
{
    GraphNode = InNode;   
    this->UpdateGraphNode();
}