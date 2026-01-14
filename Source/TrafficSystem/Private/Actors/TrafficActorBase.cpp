// © Felix Courteau-Boutin All Right Reserved

#include "Actors/TrafficActorBase.h"
#include "Components/TrafficFrontSensorComponent.h"
#include "Components/TrafficSplineFollowerComponent.h"

ATrafficActorBase::ATrafficActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineFollowerComponent = CreateDefaultSubobject<UTrafficSplineFollowerComponent>("SplineFollowerComponent");
	
	TrafficFrontSensorComponent = CreateDefaultSubobject<UTrafficFrontSensorComponent>("TrafficFrontSensorComponent");
	TrafficFrontSensorComponent->SetupAttachment(RootComponent);
	TrafficFrontSensorComponent->OnBlockStateChanged.AddDynamic(this, &ATrafficActorBase::OnTrafficBlockStateChanged);
}

void ATrafficActorBase::OnTrafficBlockStateChanged(bool bIsBlocked, AActor* TrafficBlocker)
{
	if (!bIsBlocked)
	{
		bIsBlockedByTraffic = false;
		return;
	}
	
	if (!SplineFollowerComponent) return;

	bIsBlockedByTraffic = SplineFollowerComponent->ShouldYieldTo(TrafficBlocker);
}

void ATrafficActorBase::SetForcedMove_Implementation(bool bAllowMove)
{
	if (!SplineFollowerComponent)
		return;

	SplineFollowerComponent->SetForcedMove(bAllowMove);
}

void ATrafficActorBase::SetIsBlockedByTraffic_Implementation(bool bIsBlocked)
{
	bIsBlockedByTraffic = bIsBlocked;
}

void ATrafficActorBase::SetIsBlockedByLane_Implementation(bool bIsBlocked)
{
	bIsBlockedByLane = bIsBlocked;
}

bool ATrafficActorBase::GetCanBlockTraffic_Implementation() const
{
	return bCanBlockTraffic;	
}

float ATrafficActorBase::GetDistanceOnSpline_Implementation() const
{
	return SplineFollowerComponent
		? SplineFollowerComponent->GetDistanceAlongSpline()
		: 0.f;
}

int32 ATrafficActorBase::GetTrafficPriority_Implementation() const
{
	if (!SplineFollowerComponent) return 0;
	
	return SplineFollowerComponent->GetTrafficFollowerInfo().Priority;
}

int32 ATrafficActorBase::GetTrafficUniqueID_Implementation() const
{
	if (!SplineFollowerComponent) return 0;
	
	return SplineFollowerComponent->GetTrafficFollowerInfo().UniqueID;
}

bool ATrafficActorBase::GetIsBlockedByTraffic_Implementation() const
{
	return bIsBlockedByTraffic;
}

bool ATrafficActorBase::GetIsBlockedByLane_Implementation() const
{
	return bIsBlockedByLane;
}

bool ATrafficActorBase::GetIsBlocked_Implementation() const
{
	return bIsBlockedByTraffic || bIsBlockedByLane;
}

bool ATrafficActorBase::GetIsBlockedByActor_Implementation(const AActor* Actor) const
{
	return TrafficFrontSensorComponent ? TrafficFrontSensorComponent->IsBlockedByActor(Actor) : false;
}
