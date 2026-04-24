// Copyright Epic Games, Inc. All Rights Reserved.


#include "MPAHDPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

void AMPAHDPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMPAHDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}