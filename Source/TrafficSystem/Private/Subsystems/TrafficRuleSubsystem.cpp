// © Felix Courteau-Boutin All Right Reserved

#include "Subsystems/TrafficRuleSubsystem.h"
#include "Components/TrafficAgentComponent.h"

ETrafficRightOfWay UTrafficRuleSubsystem::ComputeRightOfWay(const UTrafficAgentComponent* Agent) const
{
	if (!Agent)
	{
		return ETrafficRightOfWay::Stop;
	}

	// Currently delegates to the agent’s basic evaluation.
	// Later: include intersection reservations, priority, crosswalk occupancy, etc.
	return Agent->EvaluateRightOfWay();
}
