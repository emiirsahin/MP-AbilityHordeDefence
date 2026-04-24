
#include "AbilitySystem/Actors/AbilityActorBase.h"
#include "AbilitySystem/Objects/ProjectileAbilityInstance.h"
#include "AbilitySystem/DataAssets/ProjectileAbilityDefinition.h"

void UProjectileAbilityInstance::Initialize(UAbilityDefinition* InAbilityDefinition,
	UAbilityComponent* InOwningAbilityComponent, int32 InSlotIndex)
{
	Super::Initialize(InAbilityDefinition, InOwningAbilityComponent, InSlotIndex);
	
	if (UProjectileAbilityDefinition* ProjectileDefinition = Cast<UProjectileAbilityDefinition>(InAbilityDefinition))
	{
		AbilityActorClass = ProjectileDefinition->AbilityActorClass;
	}
	
}
AAbilityActorBase* UProjectileAbilityInstance::SpawnAbilityActorAtOwner()
{
	if (!OwningActor || !OwningActor->HasAuthority())
	{
		return nullptr;
	}

	if (!AbilityActorClass)
	{
		return nullptr;
	}

	UWorld* World = OwningActor->GetWorld();
	if (!World)
	{
		return nullptr;
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwningActor;
	SpawnParams.Instigator = Cast<APawn>(OwningActor);
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAbilityActorBase* SpawnedActor = World->SpawnActor<AAbilityActorBase>(
		AbilityActorClass,
		OwningActor->GetActorTransform(),
		SpawnParams
	);

	if (SpawnedActor)
	{
		SpawnedActor->InitializeAbilityActor(
			OwningActor,
			OwningAbilityComponent
		);
	}

	return SpawnedActor;
}

void UProjectileAbilityInstance::CommitActivation()
{
	Super::CommitActivation();

	SpawnAbilityActorAtOwner();
}
