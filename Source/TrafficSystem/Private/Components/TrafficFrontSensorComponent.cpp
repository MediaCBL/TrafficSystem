// © Felix Courteau-Boutin All Right Reserved

#include "Components/TrafficFrontSensorComponent.h"
#include "Interfaces/TrafficVehicleInterface.h"

UTrafficFrontSensorComponent::UTrafficFrontSensorComponent()
{
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetGenerateOverlapEvents(true);

	SetCollisionObjectType(ECC_WorldDynamic);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(ECC_Vehicle, ECR_Overlap);

	//SetBoxExtent(FVector(200.f, 80.f, 60.f));
	//SetRelativeLocation(FVector(200.f, 0.f, 40.f));

	PrimaryComponentTick.bCanEverTick = false;
}

bool UTrafficFrontSensorComponent::IsBlockedByActor(const AActor* Actor) const
{
	return BlockingActors.Contains(Actor);
}

void UTrafficFrontSensorComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(
		this, &UTrafficFrontSensorComponent::HandleBeginOverlap);

	OnComponentEndOverlap.AddDynamic(
		this, &UTrafficFrontSensorComponent::HandleEndOverlap);
}

void UTrafficFrontSensorComponent::HandleBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == GetOwner())
	{
		return;
	}

	if (OtherActor->Implements<UTrafficVehicleInterface>())
	{
		if (ITrafficVehicleInterface::Execute_GetCanBlockTraffic(OtherActor))
		{
			BlockingActors.Add(OtherActor);
			UpdateBlockedState();
		}
	}
}

void UTrafficFrontSensorComponent::HandleEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (!OtherActor)
	{
		return;
	}

	BlockingActors.Remove(OtherActor);
	BlockingActors.Num() > 0 ? UpdateBlockedState() : OnBlockStateChanged.Broadcast(false, nullptr);
}

void UTrafficFrontSensorComponent::UpdateBlockedState() const
{
	const bool bBlocked = IsBlocked();
	for (TObjectPtr<AActor> Actor : BlockingActors)
	{
		OnBlockStateChanged.Broadcast(bBlocked, Actor);
	}	
}
