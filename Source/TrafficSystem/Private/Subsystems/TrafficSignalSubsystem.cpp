// © Felix Courteau-Boutin All Right Reserved

#include "Subsystems/TrafficSignalSubsystem.h"
#include "Actors/TrafficSignalActor.h"

void UTrafficSignalSubsystem::RegisterSignal(ATrafficSignalActor* Signal)
{
	if (!Signal)
	{
		return;
	}

	Signals.AddUnique(Signal);
}

void UTrafficSignalSubsystem::UnregisterSignal(ATrafficSignalActor* Signal)
{
	if (!Signal)
	{
		return;
	}

	Signals.RemoveSingleSwap(Signal);
}
