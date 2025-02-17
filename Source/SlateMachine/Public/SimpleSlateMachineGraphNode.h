
#include "SGraphNode.h"

class SSimpleStateGraphNode : public SGraphNode
{
public:
    SLATE_BEGIN_ARGS(SSimpleStateGraphNode) {}
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs);
};