// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficSplineSpawner.generated.h"

class USplineComponent;

UCLASS()
class TRAFFICSYSTEM_API ATrafficSplineSpawner : public AActor
{
	GENERATED_BODY()

public:
	ATrafficSplineSpawner();

protected:
	virtual void BeginPlay() override;

public:
	/** Lane or sidewalk spline */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Traffic|Spline")
	TObjectPtr<USplineComponent> Spline;

	/** Actor class to spawn (car, pedestrian, etc.) */
	UPROPERTY(EditAnywhere, Category="Traffic|Spawner")
	TSubclassOf<AActor> AgentClass;

	/** Number of agents to spawn */
	UPROPERTY(EditAnywhere, Category="Traffic|Spawner")
	int32 SpawnCount = 1;

	/** Distance between agents along the spline */
	UPROPERTY(EditAnywhere, Category="Traffic|Spawner")
	float SpawnSpacing = 300.f;

	/** Initial speed for spline follower */
	UPROPERTY(EditAnywhere, Category="Traffic|Spawner")
	float InitialSpeed = 300.f;

	/** Spawn agents */
	UFUNCTION(BlueprintCallable, Category="Traffic|Spawner")
	void SpawnAgents();
};
