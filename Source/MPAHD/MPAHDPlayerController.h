
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPAHDPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

UCLASS(abstract)
class AMPAHDPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
};
