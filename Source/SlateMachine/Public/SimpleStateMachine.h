#pragma once

#include "CoreMinimal.h"
#include "Delegates/Delegate.h"
#include "UObject/WeakObjectPtrTemplates.h"
#include "SimpleStateMachine.generated.h"

DECLARE_DYNAMIC_DELEGATE(FUpdateStateMachine);


USTRUCT(BlueprintType)
struct SLATEMACHINE_API FSimpleState
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName State;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> SubsequentStates;
};


UCLASS(Blueprintable)
class SLATEMACHINE_API USimpleStateMachine : public UObject
{
public:
    GENERATED_BODY()
private:
    static FSimpleState EmptyState;
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName CurrentState;
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TMap<FName, FSimpleState> States;

    UFUNCTION(BlueprintCallable)
    void SetCurrentState(FName State);
    
    UFUNCTION(BlueprintCallable)
    void GetState(FName State, FSimpleState& SimpleState);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FUpdateStateMachine Evaluate;
};
