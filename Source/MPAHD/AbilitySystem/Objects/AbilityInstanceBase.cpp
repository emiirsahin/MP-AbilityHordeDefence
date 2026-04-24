
#include "AbilitySystem/Objects/AbilityInstanceBase.h"
#include "AbilitySystem/Components/AbilityComponent.h"
#include "AbilitySystem/DataAssets/AbilityDefinition.h"
#include "GameFramework/Actor.h"

void UAbilityInstanceBase::Initialize(
	UAbilityDefinition* InAbilityDefinition,
	UAbilityComponent* InOwningAbilityComponent,
	int32 InSlotIndex)
{
	AbilityDefinition = InAbilityDefinition;
	OwningAbilityComponent = InOwningAbilityComponent;
	SlotIndex = InSlotIndex;

	OwningActor = nullptr;
	if (OwningAbilityComponent)
	{
		OwningActor = OwningAbilityComponent->GetOwner();
	}

	CurrentCooldown = 0.0f;
	if (AbilityDefinition)
	{
		CurrentCooldown = AbilityDefinition->Cooldown;
	}

	CooldownRemaining = 0.0f;
	bIsBlocked = false;
	bIsInitialized = true;
}

bool UAbilityInstanceBase::CanActivate() const
{
	if (!bIsInitialized)
	{
		return false;
	}

	if (!AbilityDefinition)
	{
		return false;
	}

	if (!OwningAbilityComponent || !OwningActor)
	{
		return false;
	}

	if (bIsBlocked)
	{
		return false;
	}

	if (IsOnCooldown())
	{
		return false;
	}

	return true;
}

bool UAbilityInstanceBase::Activate()
{
	if (!CanActivate())
	{
		return false;
	}

	CommitActivation();
	return true;
}

void UAbilityInstanceBase::CommitActivation()
{
	StartCooldown();

	GEngine->AddOnScreenDebugMessage(-1, 7.0f, FColor::Red, TEXT("kabüüm"));
}

void UAbilityInstanceBase::StartCooldown()
{
	CooldownRemaining = FMath::Max(0.0f, CurrentCooldown);
}

void UAbilityInstanceBase::TickAbility(float DeltaTime)
{
	if (CooldownRemaining > 0.0f)
	{
		CooldownRemaining = FMath::Max(0.0f, CooldownRemaining - DeltaTime);
	}
}

void UAbilityInstanceBase::ResetRuntimeState()
{
	CooldownRemaining = 0.0f;
	bIsBlocked = false;

	if (AbilityDefinition)
	{
		CurrentCooldown = FMath::Max(0.0f, AbilityDefinition->Cooldown);
	}
	else
	{
		CurrentCooldown = 0.0f;
	}
}

bool UAbilityInstanceBase::IsOnCooldown() const
{
	return CooldownRemaining > 0.0f;
}

float UAbilityInstanceBase::GetCooldownRemaining() const
{
	return CooldownRemaining;
}

float UAbilityInstanceBase::GetCurrentCooldown() const
{
	return CurrentCooldown;
}

int32 UAbilityInstanceBase::GetSlotIndex() const
{
	return SlotIndex;
}

UAbilityDefinition* UAbilityInstanceBase::GetAbilityDefinition() const
{
	return AbilityDefinition;
}

UAbilityComponent* UAbilityInstanceBase::GetOwningAbilityComponent() const
{
	return OwningAbilityComponent;
}

AActor* UAbilityInstanceBase::GetOwningActor() const
{
	return OwningActor;
}

void UAbilityInstanceBase::SetBlocked(bool bInBlocked)
{
	bIsBlocked = bInBlocked;
}

void UAbilityInstanceBase::SetCurrentCooldown(float NewCooldown)
{
	CurrentCooldown = FMath::Max(0.0f, NewCooldown);

	if (CooldownRemaining > CurrentCooldown)
	{
		CooldownRemaining = CurrentCooldown;
	}
}

void UAbilityInstanceBase::ModifyCurrentCooldown(float Delta)
{
	SetCurrentCooldown(CurrentCooldown + Delta);
}