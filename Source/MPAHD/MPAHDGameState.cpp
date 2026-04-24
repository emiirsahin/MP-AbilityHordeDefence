#include "MPAHDGameState.h"
#include "Net/UnrealNetwork.h"

AMPAHDGameState::AMPAHDGameState()
{
	
}

void AMPAHDGameState::SetMatchPhase(EMPAHDMatchPhase NewPhase)
{
	if (!HasAuthority())
	{
		return;
	}

	if (MatchPhase == NewPhase)
	{
		return;
	}

	MatchPhase = NewPhase;
	
	HandleMatchPhaseChanged();
}

void AMPAHDGameState::HandleMatchPhaseChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("Match state changed!"));
	// Broadcast for UI
}

void AMPAHDGameState::OnRep_MatchPhase()
{
	HandleMatchPhaseChanged();
}

void AMPAHDGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPAHDGameState, MatchPhase);
}