
#include "SimpleStateMachine.h"

static FName EmptyState;

FSimpleState USimpleStateMachine::EmptyState{NAME_None};

void USimpleStateMachine::SetCurrentState(FName State)
{
    if (States.Contains(State))
    {
        CurrentState = State;
    }
};
    
void USimpleStateMachine::GetState(FName State, FSimpleState& SimpleState)
{
    FSimpleState* Result = States.Find(State);
    if (Result)
    {
        SimpleState = *Result;
    }
    else
    {

        SimpleState = FSimpleState{NAME_None};
    }
    return;
}
