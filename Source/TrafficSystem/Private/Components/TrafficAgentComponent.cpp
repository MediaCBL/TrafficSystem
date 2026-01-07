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
	switch (State)
	{
		case ETrafficSignalState::Green:
		case ETrafficSignalState::Walk:
			return ETrafficRightOfWay::Go;
		
		case ETrafficSignalState::Red:
		case ETrafficSignalState::DontWalk:
			return ETrafficRightOfWay::Stop;
		
		case ETrafficSignalState::Yellow:
		default:
			return ETrafficRightOfWay::Yield;
	}
}


