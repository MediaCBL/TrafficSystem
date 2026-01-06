// © Felix Courteau-Boutin All Right Reserved

#include "TrafficSplineFollowerComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TrafficVehicleInterface.h"

UTrafficSplineFollowerComponent::UTrafficSplineFollowerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UTrafficSplineFollowerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTrafficSplineFollowerComponent::SetSpline(USplineComponent* InSpline)
{
	Spline = InSpline;
	DistanceAlongSpline = 0.f;
	LastSplinePointIndex = INDEX_NONE;
}

void UTrafficSplineFollowerComponent::SetSpeed(float UnitsPerSecond)
{
	Speed = FMath::Max(UnitsPerSecond, 0.f);
}

void UTrafficSplineFollowerComponent::StartFollowing()
{
	if (!Spline || Speed <= 0.f)
	{
		return;
	}

	SetComponentTickEnabled(true);
}

void UTrafficSplineFollowerComponent::StopFollowing()
{
	SetComponentTickEnabled(false);
}

float UTrafficSplineFollowerComponent::GetDistanceAlongSpline() const
{
	return DistanceAlongSpline;
}

void UTrafficSplineFollowerComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Advance(DeltaTime);
}

void UTrafficSplineFollowerComponent::Advance(float DeltaTime)
{
	if (!Spline) return;
	
	if (GetOwner()->Implements<UTrafficVehicleInterface>())
	{
		if (ITrafficVehicleInterface::Execute_GetIsBlocked(GetOwner()))		
			return;		
	}

	DistanceAlongSpline += Speed * DeltaTime;

	const float SplineLength = Spline->GetSplineLength();

	if (DistanceAlongSpline >= SplineLength)
	{
		if (bLoop)
		{
			DistanceAlongSpline = FMath::Fmod(DistanceAlongSpline, SplineLength);
			LastSplinePointIndex = INDEX_NONE;
		}
		else
		{
			DistanceAlongSpline = SplineLength;
			StopFollowing();
		}
	}

	const FVector NewLocation =
		Spline->GetLocationAtDistanceAlongSpline(
			DistanceAlongSpline,
			ESplineCoordinateSpace::World
		);

	FRotator NewRotation = GetOwner()->GetActorRotation();

	if (bUseSplineRotation)
	{
		NewRotation = Spline->GetRotationAtDistanceAlongSpline(
			DistanceAlongSpline,
			ESplineCoordinateSpace::World
		);
	}

	GetOwner()->SetActorLocationAndRotation(NewLocation, NewRotation);

	// Check spline point crossing (events, intersections, signals)
	const int32 CurrentPointIndex =
		Spline->FindInputKeyClosestToWorldLocation(NewLocation);

	if (CurrentPointIndex != LastSplinePointIndex)
	{
		LastSplinePointIndex = CurrentPointIndex;
		OnSplinePointReached.Broadcast(CurrentPointIndex);
	}
}

bool UTrafficSplineFollowerComponent::IsBlocked() const
{
	return false;
}

