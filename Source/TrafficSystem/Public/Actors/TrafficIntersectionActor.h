// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "TrafficTypes.h"
#include "GameFramework/Actor.h"
#include "TrafficIntersectionActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

UCLASS()
class TRAFFICSYSTEM_API ATrafficIntersectionActor : public AActor
{
	GENERATED_BODY()

public:
	ATrafficIntersectionActor();

protected:
	virtual void BeginPlay() override;

public:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	/* ---------- Lanes ---------- */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Intersection")
	FTrafficLane NorthLane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Intersection")
	FTrafficLane SouthLane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Intersection")
	FTrafficLane EastLane;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Intersection")
	FTrafficLane WestLane;

	/* ---------- Material ---------- */

	UPROPERTY(EditAnywhere, Category="Intersection|Material")
	FName EmissiveColorParameterName = TEXT("EmissiveColor");

	/* ---------- API ---------- */

	UFUNCTION(BlueprintCallable, Category="Intersection")
	void SetLaneState(FTrafficLane& Lane, ETrafficLightState NewState);

	UFUNCTION(BlueprintCallable, Category="Intersection")
	bool CanVehiclePass(const FTrafficLane& Lane) const;

private:
	void InitializeLane(FTrafficLane& Lane);
	void UpdateLaneVisuals(FTrafficLane& Lane);
	FLinearColor GetColorForState(ETrafficLightState State) const;
};
