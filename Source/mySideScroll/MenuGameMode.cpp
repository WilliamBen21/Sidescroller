// Copyright Epic Games, Inc. All Rights Reserved.

#include "MenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"

// Initialize static variable
ECharacterType AMenuGameMode::StaticSelectedCharacterType = ECharacterType::SideScrolling;

AMenuGameMode::AMenuGameMode()
{
	// Set default pawn class to nullptr since we don't need a pawn in the menu
	DefaultPawnClass = nullptr;
	
	// Set default maps for each character type
	SideScrollingMapName = TEXT("SideScrollingLevel");
	PlatformingMapName = TEXT("PlatformingLevel");
	CombatMapName = TEXT("CombatLevel");
	
	SelectedCharacterType = ECharacterType::SideScrolling;
}

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// Show mouse cursor
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;

		// Set input mode to UI only
		FInputModeUIOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		// Create and display the character selection widget
		if (CharacterSelectionWidgetClass)
		{
			CharacterSelectionWidget = CreateWidget<UCharacterSelectionWidget>(PlayerController, CharacterSelectionWidgetClass);
			if (CharacterSelectionWidget)
			{
				CharacterSelectionWidget->AddToViewport();
				CharacterSelectionWidget->OnCharacterSelected.AddDynamic(this, &AMenuGameMode::OnCharacterSelected);
				
				// Set widget focus for controller input
				CharacterSelectionWidget->SetKeyboardFocus();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CharacterSelectionWidgetClass is not set in MenuGameMode"));
		}
	}
}

void AMenuGameMode::OnCharacterSelected(ECharacterType CharacterType)
{
	UE_LOG(LogTemp, Log, TEXT("Character selected: %d"), (int32)CharacterType);
	
	SelectedCharacterType = CharacterType;
	SetSelectedCharacterType(CharacterType);
	
	// Add a small delay before transitioning to make the selection feel more responsive
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, CharacterType]()
	{
		StartGameWithCharacter(CharacterType);
	}, 0.5f, false);
}

void AMenuGameMode::StartGameWithCharacter(ECharacterType CharacterType)
{
	FString MapName = GetMapNameForCharacter(CharacterType);
	
	if (!MapName.IsEmpty())
	{
		// Store the selected character type
		SetSelectedCharacterType(CharacterType);
		
		// Load the appropriate level
		UGameplayStatics::OpenLevel(this, FName(*MapName));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No map configured for character type: %d"), (int32)CharacterType);
		
		// Fallback: Load a default level
		UGameplayStatics::OpenLevel(this, FName("DefaultLevel"));
	}
}

FString AMenuGameMode::GetMapNameForCharacter(ECharacterType CharacterType) const
{
	switch (CharacterType)
	{
	case ECharacterType::SideScrolling:
		return SideScrollingMapName;
	case ECharacterType::Platforming:
		return PlatformingMapName;
	case ECharacterType::Combat:
		return CombatMapName;
	default:
		return SideScrollingMapName; // Default fallback
	}
}

ECharacterType AMenuGameMode::GetSelectedCharacterType()
{
	return StaticSelectedCharacterType;
}

void AMenuGameMode::SetSelectedCharacterType(ECharacterType CharacterType)
{
	StaticSelectedCharacterType = CharacterType;
} 