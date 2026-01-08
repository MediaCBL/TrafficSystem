// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficTypes.h"
#include "TrafficSignalActor.generated.h"+

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTrafficSignalChanged, ATrafficSignalActor*, Signal, ETrafficSignalState, NewState);

UCLASS()
class TRAFFICSYSTEM_API ATrafficSignalActor : public AActor
{
	GENERATED_BODY()

public:
	ATrafficSignalActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Traffic")
	ETrafficSignalState SignalState = ETrafficSignalState::Red;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Traffic")
	ETrafficLaneOrientation LaneOrientation = ETrafficLaneOrientation::North;
	
	UFUNCTION(BlueprintCallable, Category="Traffic")
	void SetSignalState(ETrafficSignalState NewState);

	UFUNCTION(BlueprintCallable, Category="Traffic")
	ETrafficSignalState GetSignalState() const { return SignalState; }

	UPROPERTY(BlueprintAssignable, Category="Traffic")
	FOnTrafficSignalChanged OnSignalChanged;

protected:
	virtual void BeginPlay() override;
};
