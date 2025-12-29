// © Felix Courteau-Boutin All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TrafficTypes.h"
#include "TrafficRuleSubsystem.generated.h"

class UTrafficAgentComponent;

UCLASS()
class TRAFFICSYSTEM_API UTrafficRuleSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Central place for default rules (later: data assets, per-city profiles, etc.)
	UFUNCTION(BlueprintCallable, Category="Traffic|Rules")
	ETrafficRightOfWay ComputeRightOfWay(const UTrafficAgentComponent* Agent) const;
};
