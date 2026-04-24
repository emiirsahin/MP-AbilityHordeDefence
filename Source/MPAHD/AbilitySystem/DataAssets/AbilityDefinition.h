#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilityDefinition.generated.h"

class UAbilityInstanceBase;

UCLASS()
class MPAHD_API UAbilityDefinition : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Internal identifier used by code/systems */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FName AbilityID = NAME_None;

	/** Gameplay tags for filtering and upgrade targeting */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FGameplayTagContainer AbilityTags;

	/** Player-facing ability name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FText DisplayName;

	/** Player-facing description */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FText Description;

	/** UI icon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|UI")
	TObjectPtr<UTexture2D> Icon = nullptr;

	/** Base cooldown in seconds */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Activation", meta = (ClampMin = "0.0"))
	float Cooldown = 0.0f;

	/** Runtime ability instance class created for this definition */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Runtime")
	TSubclassOf<UAbilityInstanceBase> AbilityInstanceClass;
};