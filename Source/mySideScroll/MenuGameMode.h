// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CharacterSelectionWidget.h"
#include "MenuGameMode.generated.h"

/**
 * Game Mode for the character selection menu
 * Handles the transition from menu to gameplay
 */
UCLASS()
class MYSIDESCROLL_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMenuGameMode();

protected:
	virtual void BeginPlay() override;

public:
	/** Character selection widget class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UCharacterSelectionWidget> CharacterSelectionWidgetClass;

	/** Currently displayed character selection widget */
	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UCharacterSelectionWidget> CharacterSelectionWidget;

	/** Maps to load for each character type */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FString SideScrollingMapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FString PlatformingMapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FString CombatMapName;

	/** Currently selected character type */
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	ECharacterType SelectedCharacterType;

protected:
	/** Called when a character is selected */
	UFUNCTION()
	void OnCharacterSelected(ECharacterType CharacterType);

	/** Start the game with the selected character */
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGameWithCharacter(ECharacterType CharacterType);

	/** Get the appropriate map name for the character type */
	UFUNCTION(BlueprintCallable, Category = "Game")
	FString GetMapNameForCharacter(ECharacterType CharacterType) const;

public:
	/** Static function to get the selected character from anywhere */
	UFUNCTION(BlueprintCallable, Category = "Game")
	static ECharacterType GetSelectedCharacterType();

	/** Static function to set the selected character */
	UFUNCTION(BlueprintCallable, Category = "Game")
	static void SetSelectedCharacterType(ECharacterType CharacterType);

private:
	/** Static variable to store selected character across level transitions */
	static ECharacterType StaticSelectedCharacterType;
}; 