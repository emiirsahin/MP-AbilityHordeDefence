
#include "AbilitySystem/Objects/AbilitySpecific/Internal/ExplosionAreaAbilityInstance.h"
#include "AbilitySystem/Actors/AbilityActorBase.h"
#include "AbilitySystem/DataAssets/AbilitySpecific/Internal/ExplosionAreaAbilityDefinition.h"
#include "AbilitySystem/Actors/AbilitySpecific/FireballAbilityActor.h"

void UExplosionAreaAbilityInstance::CommitActivation()
{
	Super::CommitActivation();

	SpawnAbilityActor();
}

void UExplosionAreaAbilityInstance::Initialize(UAbilityDefinition* InAbilityDefinition,
	UAbilityComponent* InOwningAbilityComponent, int32 InSlotIndex)
{
	Super::Initialize(InAbilityDefinition, InOwningAbilityComponent, InSlotIndex);

	if (UExplosionAreaAbilityDefinition* ExplosiveAreaAbilityDefinition = Cast<UExplosionAreaAbilityDefinition>(InAbilityDefinition))
	{
		BaseExplosionDamage = ExplosiveAreaAbilityDefinition->BaseExplosionDamage;
		ExplosionRadius = ExplosiveAreaAbilityDefinition->ExplosionRadius;
		ExplosionDamageFalloffCurve = ExplosiveAreaAbilityDefinition->ExplosionDamageFalloffCurve;
	}
}

AAbilityActorBase* UExplosionAreaAbilityInstance::SpawnAbilityActor()
{
	if (!AbilityActorClass || !OwningFireball)
	{
		return nullptr;
	}

	UWorld* World = OwningFireball->GetWorld();
	if (!World)
	{
		return nullptr;
	}

	FVector SpawnLocation = OwningFireball->GetActorLocation();

	AAbilityActorBase* SpawnedActor = World->SpawnActor<AAbilityActorBase>(
		AbilityActorClass,
		SpawnLocation,
		OwningFireball->GetActorRotation()
	);

	return SpawnedActor;
}

void UExplosionAreaAbilityInstance::SetOwningFireball(AFireballAbilityActor* InFireball)
{
	OwningFireball = InFireball;
}