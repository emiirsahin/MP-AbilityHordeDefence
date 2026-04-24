#include "MPAHDPlayerState.h"

#include "MPAHDGameMode.h"
#include "Net/UnrealNetwork.h"

AMPAHDPlayerState::AMPAHDPlayerState()
{
	bReplicates = true;
}

void AMPAHDPlayerState::SetReady_Server(bool bNewReady)
{
	// Only authority changes state
	if (!HasAuthority())
	{
		return;
	}

	if (bReady == bNewReady)
	{
		return;
	}

	bReady = bNewReady;

	if (bReady)
	{
		if (AMPAHDGameMode* GM = GetWorld()->GetAuthGameMode<AMPAHDGameMode>())
		{
			GM->TryStartMatch();
		}
	}
	
	HandleReadyChanged();
}

void AMPAHDPlayerState::HandleReadyChanged()
{
	// todo
	UE_LOG(LogTemp, Warning, TEXT("Ready changed!"));
}

void AMPAHDPlayerState::OnRep_Ready()
{
	HandleReadyChanged();
}

void AMPAHDPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMPAHDPlayerState, bReady);
}