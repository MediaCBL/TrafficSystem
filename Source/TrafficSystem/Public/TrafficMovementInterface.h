// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TrafficMovementInterface.generated.h"

UINTERFACE(BlueprintType)
class TRAFFICSYSTEM_API UTrafficMovementInterface : public UInterface
{
	GENERATED_BODY()
};

class TRAFFICSYSTEM_API ITrafficMovementInterface
{
	GENERATED_BODY()

public:
	// Called by AI/BT tasks or generic logic.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Traffic|Movement")
	void Traffic_Move(float DesiredSpeed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Traffic|Movement")
	void Traffic_Stop();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Traffic|Movement")
	bool Traffic_IsBlocked() const;
};
