// © Felix Courteau-Boutin All Right Reserved

#include "Actors/TrafficSignalActor.h"

ATrafficSignalActor::ATrafficSignalActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATrafficSignalActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATrafficSignalActor::SetSignalState(ETrafficSignalState NewState)
{
	if (SignalState == NewState)
	{
		return;
	}

	SignalState = NewState;
	OnSignalChanged.Broadcast(this, SignalState);
}

