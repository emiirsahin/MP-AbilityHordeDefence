
#include "AbilityComponent.h"
#include "AbilitySystem/DataAssets/AbilityDefinition.h"
#include "AbilitySystem/Objects/AbilityInstanceBase.h"

UAbilityComponent::UAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeAbilities();
}

void UAbilityComponent::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UAbilityInstanceBase* AbilityInstance : AbilityInstances)
	{
		if (!AbilityInstance)
		{
			continue;
		}

		AbilityInstance->TickAbility(DeltaTime);
	}
}

void UAbilityComponent::InitializeAbilities()
{
	AbilityInstances.SetNum(3);

	for (int32 SlotIndex = 0; SlotIndex < AbilityInstances.Num(); ++SlotIndex)
	{
		if (!InitialAbilityDefinitions.IsValidIndex(SlotIndex))
		{
			continue;
		}

		UAbilityDefinition* AbilityDefinition = InitialAbilityDefinitions[SlotIndex];
		if (!AbilityDefinition)
		{
			continue;
		}

		AssignAbilityToSlot(SlotIndex, AbilityDefinition);
	}

}

bool UAbilityComponent::IsValidAbilitySlot(int32 SlotIndex) const
{
	return SlotIndex >= 0 && SlotIndex < 3;
}

bool UAbilityComponent::AssignAbilityToSlot(int32 SlotIndex, UAbilityDefinition* AbilityDefinition)
{
	if (!IsValidAbilitySlot(SlotIndex))
	{
		return false;
	}

	if (!AbilityDefinition)
	{
		return false;
	}

	if (!AbilityDefinition->AbilityInstanceClass)
	{
		return false;
	}

	UAbilityInstanceBase* AbilityInstance = NewObject<UAbilityInstanceBase>(
		this,
		AbilityDefinition->AbilityInstanceClass);

	if (!AbilityInstance)
	{
		return false;
	}

	AbilityInstance->Initialize(AbilityDefinition, this, SlotIndex);
	AbilityInstances[SlotIndex] = AbilityInstance;
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, FString::Printf(TEXT("Ability added to slot: %d"), SlotIndex));
	
	return true;
}

UAbilityInstanceBase* UAbilityComponent::GetAbilityInstanceBySlot(int32 SlotIndex) const
{
	if (!IsValidAbilitySlot(SlotIndex))
	{
		return nullptr;
	}

	return AbilityInstances[SlotIndex];
}

bool UAbilityComponent::TryActivateAbilityBySlot(int32 SlotIndex)
{
	UAbilityInstanceBase* AbilityInstance = GetAbilityInstanceBySlot(SlotIndex);
	if (!AbilityInstance)
	{
		return false;
	}

	return AbilityInstance->Activate();
}