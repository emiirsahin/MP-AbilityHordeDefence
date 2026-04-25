
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityInstanceBase.generated.h"

class UAbilityDefinition;
class UAbilityComponent;

UCLASS(BlueprintType, Blueprintable)
class MPAHD_API UAbilityInstanceBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(
		UAbilityDefinition* InAbilityDefinition,
		UAbilityComponent* InOwningAbilityComponent,
		int32 InSlotIndex);

	virtual bool CanActivate() const;
	virtual bool Activate();
	virtual void CommitActivation();
	virtual void StartCooldown();
	virtual void TickAbility(float DeltaTime);
	virtual void ResetRuntimeState();

	bool IsOnCooldown() const;
	float GetCooldownRemaining() const;
	float GetCurrentCooldown() const;
	int32 GetSlotIndex() const;

	UAbilityDefinition* GetAbilityDefinition() const;
	UAbilityComponent* GetOwningAbilityComponent() const;
	AActor* GetOwningActor() const;

	void SetBlocked(bool bInBlocked);
	void SetCurrentCooldown(float NewCooldown);
	void ModifyCurrentCooldown(float Delta);

protected:
	UPROPERTY()
	TObjectPtr<UAbilityDefinition> AbilityDefinition = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilityComponent> OwningAbilityComponent = nullptr;

	UPROPERTY()
	TObjectPtr<AActor> OwningActor = nullptr;

	UPROPERTY()
	int32 SlotIndex = INDEX_NONE;

	UPROPERTY()
	float CurrentCooldown = 0.0f;

	UPROPERTY()
	float CooldownRemaining = 0.0f;

	UPROPERTY()
	bool bIsBlocked = false;

	UPROPERTY()
	bool bIsInitialized = false;

	UPROPERTY()
	bool bIsInternal = false;
};