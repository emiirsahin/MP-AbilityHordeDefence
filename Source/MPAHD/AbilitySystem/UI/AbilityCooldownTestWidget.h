
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityCooldownTestWidget.generated.h"

class UAbilityComponent;

UCLASS()
class MPAHD_API UAbilityCooldownTestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Abilities")
	UAbilityComponent* AbilityComponent;
	
};
