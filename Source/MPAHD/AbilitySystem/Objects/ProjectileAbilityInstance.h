
#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Objects/AbilityInstanceBase.h"
#include "ProjectileAbilityInstance.generated.h"

class AAbilityActorBase;

UCLASS()
class MPAHD_API UProjectileAbilityInstance : public UAbilityInstanceBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Actor")
	AAbilityActorBase* SpawnAbilityActorAtOwner();

	UFUNCTION(BlueprintPure, Category = "Ability|Actor")
	TSubclassOf<AAbilityActorBase> GetAbilityActorClass() const { return AbilityActorClass; }

protected:
	virtual void CommitActivation() override;
	virtual void Initialize(
		UAbilityDefinition* InAbilityDefinition,
		UAbilityComponent* InOwningAbilityComponent,
		int32 InSlotIndex) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAbilityActorBase> AbilityActorClass;
};