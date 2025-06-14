// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../CharacterSelectionWidget.h"
#include "SideScrollingGameMode.generated.h"

class USideScrollingUI;
class ASideScrollingCharacter;
class APlatformingCharacter;
class ACombatCharacter;

/**
 *  Enhanced Side Scrolling Game Mode
 *  Spawns and manages the game UI
 *  Counts pickups collected by the player
 *  Supports character selection from menu
 */
UCLASS(abstract)
class ASideScrollingGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASideScrollingGameMode();
	
protected:

	/** Class of UI widget to spawn when the game starts */
	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<USideScrollingUI> UserInterfaceClass;

	/** User interface widget for the game */
	UPROPERTY(BlueprintReadOnly, Category="UI")
	TObjectPtr<USideScrollingUI> UserInterface;

	/** Number of pickups collected by the player */
	UPROPERTY(BlueprintReadOnly, Category="Picups")
	int32 PickupsCollected = 0;

	/** Character classes for different types */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Characters")
	TSubclassOf<ASideScrollingCharacter> SideScrollingCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Characters")
	TSubclassOf<APlatformingCharacter> PlatformingCharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Characters")
	TSubclassOf<ACombatCharacter> CombatCharacterClass;

protected:

	/** Initialization */
	virtual void BeginPlay() override;

	/** Override to spawn the selected character type */
	virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, AActor* StartSpot) override;

	/** Get the appropriate character class based on selection */
	TSubclassOf<APawn> GetSelectedCharacterClass() const;

public:

	/** Receives an interaction event from another actor */
	virtual void ProcessPickup();
};
