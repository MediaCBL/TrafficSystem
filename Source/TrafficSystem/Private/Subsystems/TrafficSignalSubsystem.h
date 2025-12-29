// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TrafficSignalSubsystem.generated.h"

class ATrafficSignalActor;

UCLASS()
class TRAFFICSYSTEM_API UTrafficSignalSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Traffic|Signals")
	void RegisterSignal(ATrafficSignalActor* Signal);

	UFUNCTION(BlueprintCallable, Category="Traffic|Signals")
	void UnregisterSignal(ATrafficSignalActor* Signal);

	UFUNCTION(BlueprintCallable, Category="Traffic|Signals")
	const TArray<ATrafficSignalActor*>& GetSignals() const { return Signals; }

private:
	UPROPERTY()
	TArray<ATrafficSignalActor*> Signals;
};
