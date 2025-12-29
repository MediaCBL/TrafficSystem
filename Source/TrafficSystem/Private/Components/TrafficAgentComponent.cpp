// © Felix Courteau-Boutin All Right Reserved

#include "Components/TrafficAgentComponent.h"
#include "Actors/TrafficSignalActor.h"

UTrafficAgentComponent::UTrafficAgentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTrafficAgentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTrafficAgentComponent::SetRelevantSignal(ATrafficSignalActor* InSignal)
{
	RelevantSignal = InSignal;
}

ETrafficRightOfWay UTrafficAgentComponent::EvaluateRightOfWay() const
{
	if (!RelevantSignal)
	{
		return ETrafficRightOfWay::Go;
	}

	const ETrafficSignalState State = RelevantSignal->GetSignalState();

	// Basic default policy:
	// - Vehicles: Green => Go, Yellow => Yield, Red => Stop
	// - Pedestrians: Walk => Go, Don'tWalk/Red => Stop, others => Yield
	if (bIsPedestrian)
	{
		if (State == ETrafficSignalState::Walk) return ETrafficRightOfWay::Go;
		if (State == ETrafficSignalState::DontWalk || State == ETrafficSignalState::Red) return ETrafficRightOfWay::Stop;
		return ETrafficRightOfWay::Yield;
	}
	else
	{
		if (State == ETrafficSignalState::Green) return ETrafficRightOfWay::Go;
		if (State == ETrafficSignalState::Yellow) return ETrafficRightOfWay::Yield;
		return ETrafficRightOfWay::Stop;
	}
}


