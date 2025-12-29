// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrafficTypes.h"
#include "TrafficAgentComponent.generated.h"

class ATrafficSignalActor;

UCLASS(ClassGroup=(Traffic), meta=(BlueprintSpawnableComponent))
class TRAFFICSYSTEM_API UTrafficAgentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTrafficAgentComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Traffic")
	bool bIsPedestrian = false;

	// Optional cached signal the agent currently cares about (set by perception/overlaps later)
	UPROPERTY(BlueprintReadOnly, Category="Traffic")
	TObjectPtr<ATrafficSignalActor> RelevantSignal;

	UFUNCTION(BlueprintCallable, Category="Traffic")
	bool HasRelevantSignal() const { return RelevantSignal != nullptr; }

	UFUNCTION(BlueprintCallable, Category="Traffic")
	void SetRelevantSignal(ATrafficSignalActor* InSignal);

	// Helper for BT tasks etc.
	UFUNCTION(BlueprintCallable, Category="Traffic")
	ETrafficRightOfWay EvaluateRightOfWay() const;

protected:
	virtual void BeginPlay() override;
};
