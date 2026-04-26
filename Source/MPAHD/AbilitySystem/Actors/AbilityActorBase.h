
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityActorBase.generated.h"

class UAbilityComponent;
class UAbilityInstanceBase;

UCLASS()
class MPAHD_API AAbilityActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAbilityActorBase();

	AActor* GetSourceActor() const { return SourceActor; }
	UAbilityComponent* GetSourceAbilityComponent() const { return SourceAbilityComponent; }
	UAbilityInstanceBase* GetSourceAbilityInstance() const { return SourceAbilityInstance; }
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	TObjectPtr<AActor> SourceActor;

	UPROPERTY()
	TObjectPtr<UAbilityComponent> SourceAbilityComponent;

	UPROPERTY()
	TObjectPtr<UAbilityInstanceBase> SourceAbilityInstance;
	
	UPROPERTY(EditDefaultsOnly, Category="Ability Actor", meta=(ClampMin="0.0"))
	float LifeTime = 0.0f;


public:
	virtual void InitializeAbilityActor(
	AActor* InSourceActor,
	UAbilityComponent* InSourceAbilityComponent,
	UAbilityInstanceBase* InSourceAbilityInstance);
};
