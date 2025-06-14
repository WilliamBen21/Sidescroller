// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "CharacterSelectionWidget.generated.h"

class ACharacterPreviewActor;

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	None			UMETA(DisplayName = "None"),
	SideScrolling	UMETA(DisplayName = "Side Scrolling"),
	Platforming		UMETA(DisplayName = "Platforming"),
	Combat			UMETA(DisplayName = "Combat")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSelected, ECharacterType, SelectedCharacter);

/**
 * Character Selection Menu Widget
 * Displays available characters and handles player selection
 */
UCLASS(BlueprintType, Blueprintable)
class MYSIDESCROLL_API UCharacterSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UCharacterSelectionWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	/** Delegate called when a character is selected */
	UPROPERTY(BlueprintAssignable, Category = "Character Selection")
	FOnCharacterSelected OnCharacterSelected;

protected:
	/** Character selection buttons */
	UPROPERTY(meta = (BindWidget))
	UButton* SideScrollingButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PlatformingButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CombatButton;

	/** Character info display */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CharacterDescriptionText;

	UPROPERTY(meta = (BindWidget))
	UImage* CharacterPreviewImage;

	/** Instructions text */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InstructionsText;

	/** Currently highlighted character */
	UPROPERTY(BlueprintReadOnly, Category = "Character Selection")
	ECharacterType CurrentSelection;

	/** Index for controller navigation */
	int32 CurrentSelectionIndex;

	/** Array of character types for controller navigation */
	TArray<ECharacterType> CharacterTypes;

	/** Reference to character preview actor in the level */
	UPROPERTY(BlueprintReadWrite, Category = "Character Selection")
	TObjectPtr<ACharacterPreviewActor> CharacterPreviewActor;

protected:
	/** Button click handlers */
	UFUNCTION()
	void OnSideScrollingButtonClicked();

	UFUNCTION()
	void OnPlatformingButtonClicked();

	UFUNCTION()
	void OnCombatButtonClicked();

	/** Character selection logic */
	UFUNCTION(BlueprintCallable, Category = "Character Selection")
	void SelectCharacter(ECharacterType CharacterType);

	/** Update UI based on current selection */
	UFUNCTION(BlueprintCallable, Category = "Character Selection")
	void UpdateCharacterInfo(ECharacterType CharacterType);

	/** Controller navigation */
	void NavigateLeft();
	void NavigateRight();
	void ConfirmSelection();

	/** Helper functions */
	FText GetCharacterName(ECharacterType CharacterType) const;
	FText GetCharacterDescription(ECharacterType CharacterType) const;
	void UpdateButtonHighlight();
}; 