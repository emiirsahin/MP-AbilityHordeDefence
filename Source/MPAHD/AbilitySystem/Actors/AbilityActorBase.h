
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityActorBase.generated.h"

class UAbilityComponent;

UCLASS()
class MPAHD_API AAbilityActorBase : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilityComponent> SourceAbilityComponent;
	
public:	
	AAbilityActorBase();

	AActor* GetSourceActor() const { return SourceActor; }
	UAbilityComponent* GetSourceAbilityComponent() const { return SourceAbilityComponent; }
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY()
	TObjectPtr<AActor> SourceActor;

	UPROPERTY(EditDefaultsOnly, Category="Ability Actor", meta=(ClampMin="0.0"))
	float LifeTime = 0.0f;


public:
	virtual void InitializeAbilityActor(
	AActor* InSourceActor,
	UAbilityComponent* InSourceAbilityComponent);
};
