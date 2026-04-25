
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Objects/ActorSpawningAbilityInstance.h"
#include "FireballAbilityInstance.generated.h"

UCLASS()
class MPAHD_API UFireballAbilityInstance : public UActorSpawningAbilityInstance
{
	GENERATED_BODY()

protected:
	virtual void CommitActivation() override;
	
	virtual void Initialize(
		UAbilityDefinition* InAbilityDefinition,
		UAbilityComponent* InOwningAbilityComponent,
		int32 InSlotIndex) override;
	
	virtual AAbilityActorBase* SpawnAbilityActor() override;
	
	UPROPERTY()
	float ProjectileSpeed = 0.0f;
};