
#include "AbilitySystem/Objects/ActorSpawningAbilityInstance.h"

#include "MPAHDCharacter.h"
#include "AbilitySystem/Actors/AbilityActorBase.h"
#include "AbilitySystem/DataAssets/ActorSpawningAbilityDefinition.h"

void UActorSpawningAbilityInstance::Initialize(UAbilityDefinition* InAbilityDefinition,
                                               UAbilityComponent* InOwningAbilityComponent, int32 InSlotIndex)
{
	Super::Initialize(InAbilityDefinition, InOwningAbilityComponent, InSlotIndex);
	
	if (UActorSpawningAbilityDefinition* ProjectileDefinition = Cast<UActorSpawningAbilityDefinition>(InAbilityDefinition))
	{
		AbilityActorClass = ProjectileDefinition->AbilityActorClass;
		SpawnOffset = ProjectileDefinition->SpawnOffset;
	}
}

AAbilityActorBase* UActorSpawningAbilityInstance::SpawnAbilityActor()
{
	return nullptr;
}
