// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrafficSplineFollowerComponent.generated.h"

class USplineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnSplinePointReached,
	int32,
	PointIndex
);

UCLASS(ClassGroup=(Traffic), meta=(BlueprintSpawnableComponent))
class TRAFFICSYSTEM_API UTrafficSplineFollowerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTrafficSplineFollowerComponent();

	/** Assign the spline to follow */
	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void SetSpline(USplineComponent* InSpline);

	/** Units per second */
	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void SetSpeed(float UnitsPerSecond);

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void StartFollowing();

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void StopFollowing();

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	float GetDistanceAlongSpline() const;

	/** Fired when passing a spline point (for intersections, signals, etc.) */
	UPROPERTY(BlueprintAssignable, Category="Traffic|Spline")
	FOnSplinePointReached OnSplinePointReached;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	void Advance(float DeltaTime);
	bool IsBlocked() const;

protected:
	UPROPERTY(EditAnywhere, Category="Traffic|Spline")
	bool bUseSplineRotation = true;

	UPROPERTY(EditAnywhere, Category="Traffic|Spline")
	bool bLoop = false;

private:
	UPROPERTY()
	TObjectPtr<USplineComponent> Spline;

	float Speed = 0.f;
	float DistanceAlongSpline = 0.f;
	int32 LastSplinePointIndex = INDEX_NONE;
};

