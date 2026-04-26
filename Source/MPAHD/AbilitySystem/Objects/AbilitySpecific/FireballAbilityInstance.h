
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Objects/ActorSpawningAbilityInstance.h"
#include "FireballAbilityInstance.generated.h"

class AFireballAbilityActor;
class UExplosionAreaAbilityInstance;
class UExplosionAreaAbilityDefinition;

UCLASS()
class MPAHD_API UFireballAbilityInstance : public UActorSpawningAbilityInstance
{
	GENERATED_BODY()

public:
	friend class UFireballAbilityInstance;

	void SpawnExplosionArea(AFireballAbilityActor* InFireballActor);
	
protected:
	virtual void CommitActivation() override;
	
	virtual void Initialize(
		UAbilityDefinition* InAbilityDefinition,
		UAbilityComponent* InOwningAbilityComponent,
		int32 InSlotIndex) override;
	
	virtual AAbilityActorBase* SpawnAbilityActor() override;
	
	UPROPERTY()
	float ProjectileSpeed = 0.0f;

private:
	UPROPERTY()
	TObjectPtr<UExplosionAreaAbilityDefinition> ExplosionAreaAbilityDefinition;

	UPROPERTY()
	TObjectPtr<UExplosionAreaAbilityInstance> ExplosionAreaAbilityInstance;



	
	void InitializeInternalAbilities();
};