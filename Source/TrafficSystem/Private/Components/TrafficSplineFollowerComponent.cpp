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

void UTrafficSplineFollowerComponent::SetSpeed(float UnitsPerSecond)
{
	Speed = FMath::Max(UnitsPerSecond, 0.f);
}

void UTrafficSplineFollowerComponent::SetForcedMove(bool ForceMove)
{
	bForcedMove = ForceMove;
}

void UTrafficSplineFollowerComponent::StartFollowing(const FTrafficFollowerInfo Info)
{
	TrafficFollowerInfo = Info;
	InitializeSplineFollowerComponent();
	
	if (!Spline || Speed <= 0.f)
	{
		return;
	}

	SetComponentTickEnabled(true);
}

void UTrafficSplineFollowerComponent::InitializeSplineFollowerComponent()
{
	Spline = TrafficFollowerInfo.Spline;
	bLoop = Spline->IsClosedLoop();
	LastSplinePointIndex = INDEX_NONE;
	Speed = TrafficFollowerInfo.Speed;
	DistanceAlongSpline = TrafficFollowerInfo.DistanceAlongSpline;
}

void UTrafficSplineFollowerComponent::StopFollowing()
{
	SetComponentTickEnabled(false);
}

float UTrafficSplineFollowerComponent::GetDistanceAlongSpline() const
{
	return DistanceAlongSpline;
}

void UTrafficSplineFollowerComponent::SetDistanceAlongSpline(float Distance)
{
	DistanceAlongSpline = FMath::Clamp(Distance, 0.f, Spline->GetSplineLength());
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
		if (ITrafficVehicleInterface::Execute_GetIsBlocked(GetOwner())) return;

	const float SplineLength = Spline->GetSplineLength();
	if (SplineLength <= KINDA_SMALL_NUMBER)
		return;

	const float PreviousDistance = DistanceAlongSpline;
	DistanceAlongSpline += Speed * DeltaTime;

	bool bDidLoop = false;

	if (DistanceAlongSpline >= SplineLength)
	{
		if (bLoop)
		{
			DistanceAlongSpline = FMath::Fmod(DistanceAlongSpline, SplineLength);
			bDidLoop = true;
		}
		else
		{
			DistanceAlongSpline = SplineLength;
			StopFollowing();
			return;
		}
	}

	// Move actor
	const FVector NewLocation =
		Spline->GetLocationAtDistanceAlongSpline(
			DistanceAlongSpline,
			ESplineCoordinateSpace::World
		);

	FRotator NewRotation = GetOwner()->GetActorRotation();
	if (bUseSplineRotation)
	{
		NewRotation =
			Spline->GetRotationAtDistanceAlongSpline(
				DistanceAlongSpline,
				ESplineCoordinateSpace::World
			);
	}

	GetOwner()->SetActorLocationAndRotation(NewLocation, NewRotation);

	// ---- Spline point crossing detection (loop-safe) ----
	const int32 NumPoints = Spline->GetNumberOfSplinePoints();

	auto GetPointIndexAtDistance = [&](float Distance)
	{
		const float InputKey = Spline->GetInputKeyAtDistanceAlongSpline(Distance);
		return FMath::FloorToInt(InputKey);
	};

	const int32 PreviousPoint = GetPointIndexAtDistance(PreviousDistance);
	const int32 CurrentPoint  = GetPointIndexAtDistance(DistanceAlongSpline);

	// Normal forward progression
	if (PreviousPoint != CurrentPoint)
	{
		OnSplinePointReached.Broadcast(CurrentPoint);
		LastSplinePointIndex = CurrentPoint;
	}

	// Loop wrap: force point 0 event
	if (bDidLoop)
	{
		OnSplinePointReached.Broadcast(0);
		LastSplinePointIndex = 0;
	}
}

bool UTrafficSplineFollowerComponent::IsBlocked() const
{
	return false;
}

bool UTrafficSplineFollowerComponent::ShouldYieldTo(const AActor* Other) const
{
	if (!Other || Other == GetOwner())
		return false;

	if (!Other->Implements<UTrafficVehicleInterface>())
		return false;

	const AActor* Self = GetOwner();

	const int32 MyPriority = ITrafficVehicleInterface::Execute_GetTrafficPriority(Self);
	const int32 OtherPriority = ITrafficVehicleInterface::Execute_GetTrafficPriority(Other);

	// 1️⃣ Priority rule
	if (MyPriority != OtherPriority)
		return MyPriority < OtherPriority;

	const float MyDist = ITrafficVehicleInterface::Execute_GetDistanceOnSpline(Self);
	const float OtherDist = ITrafficVehicleInterface::Execute_GetDistanceOnSpline(Other);

	// Progress rule
	if (!FMath::IsNearlyEqual(MyDist, OtherDist))
		return MyDist < OtherDist;

	// Stable tie breaker
	const int32 MyID = ITrafficVehicleInterface::Execute_GetTrafficUniqueID(Self);
	const int32 OtherID = ITrafficVehicleInterface::Execute_GetTrafficUniqueID(Other);

	return MyID > OtherID;
}

FTrafficFollowerInfo UTrafficSplineFollowerComponent::GetTrafficFollowerInfo() const
{
	return TrafficFollowerInfo;
}
