// Copyright Epic Games, Inc. All Rights Reserved.


#include "SideScrollingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "SideScrollingUI.h"
#include "SideScrollingPickup.h"
#include "SideScrollingCharacter.h"
#include "../Variant_Platforming/PlatformingCharacter.h"
#include "../Variant_Combat/CombatCharacter.h"
#include "../CustomSideScrollCharacter.h"
#include "../MenuGameMode.h"
#include "Engine/World.h"
#include "GameFramework/PlayerStart.h"

ASideScrollingGameMode::ASideScrollingGameMode()
{
	// Set default character classes - PURE C++ VERSION
	// Use the new custom character as the default
	DefaultPawnClass = ACustomSideScrollCharacter::StaticClass();
	CustomSideScrollCharacterClass = ACustomSideScrollCharacter::StaticClass();
	SideScrollingCharacterClass = ASideScrollingCharacter::StaticClass();
	PlatformingCharacterClass = APlatformingCharacter::StaticClass();
	CombatCharacterClass = ACombatCharacter::StaticClass();
}

void ASideScrollingGameMode::BeginPlay()
{
	Super::BeginPlay();

	// create the game UI
	APlayerController* OwningPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (UserInterfaceClass)
	{
		UserInterface = CreateWidget<USideScrollingUI>(OwningPlayer, UserInterfaceClass);
	}
}

APawn* ASideScrollingGameMode::SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot)
{
	// Get the selected character class
	TSubclassOf<APawn> CharacterClass = GetSelectedCharacterClass();
	
	if (CharacterClass)
	{
		// Spawn the selected character type
		FVector SpawnLocation = StartSpot ? StartSpot->GetActorLocation() : FVector::ZeroVector;
		FRotator SpawnRotation = StartSpot ? StartSpot->GetActorRotation() : FRotator::ZeroRotator;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		APawn* SpawnedPawn = GetWorld()->SpawnActor<APawn>(CharacterClass, SpawnLocation, SpawnRotation, SpawnParams);
		
		if (SpawnedPawn)
		{
			UE_LOG(LogTemp, Log, TEXT("Spawned character of type: %s"), *CharacterClass->GetName());
			return SpawnedPawn;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to spawn character of type: %s"), *CharacterClass->GetName());
		}
	}
	
	// Fallback to default spawning
	return Super::SpawnDefaultPawnFor_Implementation(NewPlayer, StartSpot);
}

TSubclassOf<APawn> ASideScrollingGameMode::GetSelectedCharacterClass() const
{
	// Get the selected character type from the menu
	ECharacterType SelectedType = AMenuGameMode::GetSelectedCharacterType();
	
	switch (SelectedType)
	{
	case ECharacterType::SideScrolling:
		return SideScrollingCharacterClass;
	case ECharacterType::Platforming:
		return PlatformingCharacterClass;
	case ECharacterType::Combat:
		return CombatCharacterClass;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Unknown character type selected, defaulting to SideScrolling"));
		return SideScrollingCharacterClass;
	}
}

void ASideScrollingGameMode::ProcessPickup()
{
	// increment the pickups counter
	++PickupsCollected;

	// if this is the first pickup we collect, show the UI
	if (PickupsCollected == 1 && UserInterface)
	{
		UserInterface->AddToViewport(0);
	}

	// update the pickups counter on the UI
	if (UserInterface)
	{
		UserInterface->UpdatePickups(PickupsCollected);
	}
}