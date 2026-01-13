// © Felix Courteau-Boutin All Right Reserved

#include "Actors/TrafficLaneActor.h"

#include "TrafficTypes.h"
#include "Components/BoxComponent.h"
#include "Interfaces/TrafficVehicleInterface.h"

ATrafficLaneActor::ATrafficLaneActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	StopVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("StopVolume"));
	SetRootComponent(StopVolume);

	StopVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StopVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	StopVolume->SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);
	StopVolume->SetGenerateOverlapEvents(true);

	StopVolume->OnComponentBeginOverlap.AddDynamic(
		this, &ATrafficLaneActor::OnStopVolumeBeginOverlap);

	StopVolume->OnComponentEndOverlap.AddDynamic(
		this, &ATrafficLaneActor::OnStopVolumeEndOverlap);
}

void ATrafficLaneActor::SetState(ETrafficLightState NewState)
{
	CurrentState = NewState;
	SetLaneAllowsMovement(CurrentState == ETrafficLightState::Green);
}

void ATrafficLaneActor::OnStopVolumeBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor)
		return;

	if (OtherActor->GetClass()->ImplementsInterface(UTrafficVehicleInterface::StaticClass()))
	{
		VehiclesInStopVolume.Add(OtherActor);

		bool bIsBlocked = CurrentState != ETrafficLightState::Green;
		ITrafficVehicleInterface::Execute_SetIsBlockedByLane(OtherActor, bIsBlocked);
	}
}

void ATrafficLaneActor::OnStopVolumeEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!OtherActor)
		return;

	if (OtherActor->GetClass()->ImplementsInterface(UTrafficVehicleInterface::StaticClass()))
	{
		VehiclesInStopVolume.Remove(OtherActor);
		
		ITrafficVehicleInterface::Execute_SetIsBlockedByLane(OtherActor, false);
	}
}

void ATrafficLaneActor::SetLaneAllowsMovement(bool bAllow)
{
	if (bLaneAllowsMovement == bAllow)
		return;

	bLaneAllowsMovement = bAllow;

	for (TWeakObjectPtr<AActor> Vehicle : VehiclesInStopVolume)
	{
		if (!Vehicle.IsValid())
			continue;

		ITrafficVehicleInterface::Execute_SetIsBlockedByLane(Vehicle.Get(), !bLaneAllowsMovement);		
	}
}
