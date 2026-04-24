
#include "AbilityActorBase.h"

AAbilityActorBase::AAbilityActorBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
}

void AAbilityActorBase::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && LifeTime > 0.0f)
	{
		SetLifeSpan(LifeTime);
	}
}

void AAbilityActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbilityActorBase::InitializeAbilityActor(
	AActor* InSourceActor,
	UAbilityComponent* InSourceAbilityComponent)
{
	SourceActor = InSourceActor;
	SourceAbilityComponent = InSourceAbilityComponent;
}
