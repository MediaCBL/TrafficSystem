// © Felix Courteau-Boutin All Right Reserved

#include "Actors/TrafficSplineSpawner.h"

#include "Components/SplineComponent.h"
#include "Components/TrafficSplineFollowerComponent.h"
#include "Engine/World.h"

ATrafficSplineSpawner::ATrafficSplineSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("TrafficSpline"));
	SetRootComponent(Spline);
}

void ATrafficSplineSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnAgents();
}

void ATrafficSplineSpawner::SpawnAgents()
{
	if (!AgentClass || !Spline)
	{
		UE_LOG(LogTemp, Warning, TEXT("TrafficSplineSpawner: Missing AgentClass or Spline"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const float SplineLength = Spline->GetSplineLength();

	for (int32 i = 0; i < SpawnCount; ++i)
	{
		const float Distance = FMath::Clamp(
			i * SpawnSpacing,
			0.f,
			SplineLength
		);

		const FTransform SpawnTransform =
			Spline->GetTransformAtDistanceAlongSpline(
				Distance,
				ESplineCoordinateSpace::World
			);

		AActor* SpawnedActor = World->SpawnActor<AActor>(
			AgentClass,
			SpawnTransform
		);

		if (!SpawnedActor)
		{
			continue;
		}

		UTrafficSplineFollowerComponent* SplineFollower =
			SpawnedActor->FindComponentByClass<UTrafficSplineFollowerComponent>();

		if (!SplineFollower)
		{
			UE_LOG(
				LogTemp,
				Warning,
				TEXT("TrafficSplineSpawner: Spawned actor %s has no TrafficSplineFollowerComponent"),
				*SpawnedActor->GetName()
			);
			continue;
		}

		SplineFollower->SetSpline(Spline);
		SplineFollower->SetSpeed(InitialSpeed);
		SplineFollower->StartFollowing();
	}
}
