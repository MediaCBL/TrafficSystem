// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "TrafficTypes.h"
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
	void SetForcedMove(bool ForceMove);

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void StartFollowing(FTrafficFollowerInfo Info);
	void InitializeSplineFollowerComponent();

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void StopFollowing();

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	float GetDistanceAlongSpline() const;

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	void SetDistanceAlongSpline(float Distance);

	/** Fired when passing a spline point (for intersections, signals, etc.) */
	UPROPERTY(BlueprintAssignable, Category="Traffic|Spline")
	FOnSplinePointReached OnSplinePointReached;

	UFUNCTION(BlueprintCallable, Category="Traffic|Spline")
	FTrafficFollowerInfo GetTrafficFollowerInfo() const;

	UFUNCTION()
	bool ShouldYieldTo(const AActor* Other) const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(
		float DeltaTime,
		ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;

	void Advance(float DeltaTime);
	bool IsBlocked() const;

	UPROPERTY(EditAnywhere, Category="Traffic|Spline")
	bool bUseSplineRotation = true;

	UPROPERTY(EditAnywhere, Category="Traffic|Spline")
	bool bLoop = false;
	
	UPROPERTY(EditAnywhere, Category="Traffic|Spline")
	FTrafficFollowerInfo TrafficFollowerInfo;

private:
	UPROPERTY()
	TObjectPtr<USplineComponent> Spline;

	float Speed = 0.f;
	float DistanceAlongSpline = 0.f;
	int32 LastSplinePointIndex = INDEX_NONE;
	bool bForcedMove = false;
};

