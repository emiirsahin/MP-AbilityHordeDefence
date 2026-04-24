
#include "MPAHDGameMode.h"
#include "MPAHDGameState.h"
#include "MPAHDPlayerState.h"
#include "GameFramework/GameStateBase.h"

AMPAHDGameMode::AMPAHDGameMode()
{
	PlayerStateClass = AMPAHDPlayerState::StaticClass();
	GameStateClass = AMPAHDGameState::StaticClass();
}

bool AMPAHDGameMode::AreAllPlayersReady() const
{
	const AGameStateBase* GS = GameState;
	if (!GS) return false;

	for (APlayerState* PS : GS->PlayerArray)
	{
		const AMPAHDPlayerState* GCPS = Cast<AMPAHDPlayerState>(PS);
		if (!GCPS) continue;
		
		if (!GCPS->IsReady())
		{
			return false;
		}
	}
	return true;
}

void AMPAHDGameMode::TryStartMatch()
{
	// GameMode only exists on server, but I just want to do this.
	if (!HasAuthority())
	{
		return;
	}

	if (!AreAllPlayersReady())
	{
		return;
	}

	AMPAHDGameState* GS = GetGameState<AMPAHDGameState>();
	if (!GS)
	{
		return;
	}

	// safeguard from erratic ready calls.
	if (GS->GetMatchPhase() != EMPAHDMatchPhase::Lobby)
	{
		return;
	}

	GS->SetMatchPhase(EMPAHDMatchPhase::InMatch);
}
