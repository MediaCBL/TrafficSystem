// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLaneActor.generated.h"

enum class ETrafficLaneOrientation : uint8;
class UBoxComponent;
enum class ETrafficLightState : uint8;

UCLASS()
class TRAFFICSYSTEM_API ATrafficLaneActor : public AActor
{
	GENERATED_BODY()

public:
	ATrafficLaneActor();

	UFUNCTION(BlueprintCallable, Category="Traffic")
	void SetState(ETrafficLightState NewState);
	ETrafficLightState GetState() const { return CurrentState; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> StopVolume = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETrafficLaneOrientation LaneOrientation;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ETrafficLightState CurrentState;
	
	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> VehiclesInStopVolume;

	
	bool bLaneAllowsMovement;

	UFUNCTION()
	void OnStopVolumeBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
	UFUNCTION()
	void OnStopVolumeEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
	void SetLaneAllowsMovement(bool bAllow);
};
