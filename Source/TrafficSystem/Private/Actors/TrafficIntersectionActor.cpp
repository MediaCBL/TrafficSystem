// © Felix Courteau-Boutin All Right Reserved

#include "Actors/TrafficIntersectionActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ATrafficIntersectionActor::ATrafficIntersectionActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void ATrafficIntersectionActor::BeginPlay()
{
	Super::BeginPlay();

	InitializeLane(NorthLane);
	InitializeLane(SouthLane);
	InitializeLane(EastLane);
	InitializeLane(WestLane);
}

void ATrafficIntersectionActor::InitializeLane(FTrafficLane& Lane)
{
	if (!Lane.LightMesh)
	{
		return;
	}

	if (UMaterialInterface* BaseMat = Lane.LightMesh->GetMaterial(0))
	{
		Lane.DynamicMaterial =
			UMaterialInstanceDynamic::Create(BaseMat, this);
		Lane.LightMesh->SetMaterial(0, Lane.DynamicMaterial);
	}

	UpdateLaneVisuals(Lane);
}

void ATrafficIntersectionActor::SetLaneState(
	FTrafficLane& Lane,
	ETrafficLightState NewState)
{
	Lane.CurrentState = NewState;
	UpdateLaneVisuals(Lane);
}

bool ATrafficIntersectionActor::CanVehiclePass(
	const FTrafficLane& Lane) const
{
	return Lane.CurrentState == ETrafficLightState::Green;
}

void ATrafficIntersectionActor::UpdateLaneVisuals(FTrafficLane& Lane)
{
	if (!Lane.DynamicMaterial)
	{
		return;
	}

	Lane.DynamicMaterial->SetVectorParameterValue(
		EmissiveColorParameterName,
		GetColorForState(Lane.CurrentState)
	);
}

FLinearColor ATrafficIntersectionActor::GetColorForState(
	ETrafficLightState State) const
{
	switch (State)
	{
	case ETrafficLightState::Red:
		return FLinearColor(10.f, 0.f, 0.f);
	case ETrafficLightState::Yellow:
		return FLinearColor(10.f, 10.f, 0.f);
	case ETrafficLightState::Green:
		return FLinearColor(0.f, 10.f, 0.f);
	default:
		return FLinearColor::Black;
	}
}




