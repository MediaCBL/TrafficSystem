// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "TrafficFrontSensorComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnTrafficBlockStateChanged,
	bool, bIsBlocked
);

UCLASS(ClassGroup=(Traffic), meta=(BlueprintSpawnableComponent))
class TRAFFICSYSTEM_API UTrafficFrontSensorComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTrafficFrontSensorComponent();

	UFUNCTION(BlueprintCallable, Category="Traffic")
	bool IsBlocked() const { return BlockingActors.Num() > 0; }

	UPROPERTY(BlueprintAssignable, Category="Traffic")
	FOnTrafficBlockStateChanged OnBlockStateChanged;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TSet<TWeakObjectPtr<AActor>> BlockingActors;

	UFUNCTION()
	void HandleBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void HandleEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	void UpdateBlockedState() const;
};
