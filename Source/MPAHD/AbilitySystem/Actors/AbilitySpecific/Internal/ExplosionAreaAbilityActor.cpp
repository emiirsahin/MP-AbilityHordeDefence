
#include "AbilitySystem/Actors/AbilitySpecific/Internal/ExplosionAreaAbilityActor.h"

AExplosionAreaAbilityActor::AExplosionAreaAbilityActor()
{
	bReplicates = true;
	SetReplicatingMovement(true);

	PrimaryActorTick.bCanEverTick = false;
}
