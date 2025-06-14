// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterSelectionWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "CharacterPreviewActor.h"

UCharacterSelectionWidget::UCharacterSelectionWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentSelection = ECharacterType::SideScrolling;
	CurrentSelectionIndex = 0;
	
	// Initialize character types array for controller navigation
	CharacterTypes.Add(ECharacterType::SideScrolling);
	CharacterTypes.Add(ECharacterType::Platforming);
	CharacterTypes.Add(ECharacterType::Combat);
}

void UCharacterSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Bind button events
	if (SideScrollingButton)
	{
		SideScrollingButton->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::OnSideScrollingButtonClicked);
	}

	if (PlatformingButton)
	{
		PlatformingButton->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::OnPlatformingButtonClicked);
	}

	if (CombatButton)
	{
		CombatButton->OnClicked.AddDynamic(this, &UCharacterSelectionWidget::OnCombatButtonClicked);
	}

	// Set initial character info
	UpdateCharacterInfo(CurrentSelection);
	UpdateButtonHighlight();

	// Set focus to this widget for controller input
	SetKeyboardFocus();
}

FReply UCharacterSelectionWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FKey Key = InKeyEvent.GetKey();

	// Handle controller/keyboard navigation
	if (Key == EKeys::Gamepad_DPad_Left || Key == EKeys::A || Key == EKeys::Left)
	{
		NavigateLeft();
		return FReply::Handled();
	}
	else if (Key == EKeys::Gamepad_DPad_Right || Key == EKeys::D || Key == EKeys::Right)
	{
		NavigateRight();
		return FReply::Handled();
	}
	else if (Key == EKeys::Gamepad_FaceButton_Bottom || Key == EKeys::Enter || Key == EKeys::SpaceBar)
	{
		ConfirmSelection();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UCharacterSelectionWidget::OnSideScrollingButtonClicked()
{
	SelectCharacter(ECharacterType::SideScrolling);
}

void UCharacterSelectionWidget::OnPlatformingButtonClicked()
{
	SelectCharacter(ECharacterType::Platforming);
}

void UCharacterSelectionWidget::OnCombatButtonClicked()
{
	SelectCharacter(ECharacterType::Combat);
}

void UCharacterSelectionWidget::SelectCharacter(ECharacterType CharacterType)
{
	CurrentSelection = CharacterType;
	
	// Find the index for this character type
	for (int32 i = 0; i < CharacterTypes.Num(); i++)
	{
		if (CharacterTypes[i] == CharacterType)
		{
			CurrentSelectionIndex = i;
			break;
		}
	}

	UpdateCharacterInfo(CharacterType);
	UpdateButtonHighlight();

	// Broadcast the selection
	OnCharacterSelected.Broadcast(CharacterType);
}

void UCharacterSelectionWidget::UpdateCharacterInfo(ECharacterType CharacterType)
{
	if (CharacterNameText)
	{
		CharacterNameText->SetText(GetCharacterName(CharacterType));
	}

	if (CharacterDescriptionText)
	{
		CharacterDescriptionText->SetText(GetCharacterDescription(CharacterType));
	}

	// Update instructions text
	if (InstructionsText)
	{
		InstructionsText->SetText(FText::FromString(TEXT("Use Arrow Keys/D-Pad to navigate, Enter/A Button to select")));
	}

	// Update character preview
	if (CharacterPreviewActor)
	{
		CharacterPreviewActor->SetCharacterType(CharacterType);
	}
}

void UCharacterSelectionWidget::NavigateLeft()
{
	CurrentSelectionIndex--;
	if (CurrentSelectionIndex < 0)
	{
		CurrentSelectionIndex = CharacterTypes.Num() - 1;
	}

	CurrentSelection = CharacterTypes[CurrentSelectionIndex];
	UpdateCharacterInfo(CurrentSelection);
	UpdateButtonHighlight();
}

void UCharacterSelectionWidget::NavigateRight()
{
	CurrentSelectionIndex++;
	if (CurrentSelectionIndex >= CharacterTypes.Num())
	{
		CurrentSelectionIndex = 0;
	}

	CurrentSelection = CharacterTypes[CurrentSelectionIndex];
	UpdateCharacterInfo(CurrentSelection);
	UpdateButtonHighlight();
}

void UCharacterSelectionWidget::ConfirmSelection()
{
	SelectCharacter(CurrentSelection);
}

FText UCharacterSelectionWidget::GetCharacterName(ECharacterType CharacterType) const
{
	switch (CharacterType)
	{
	case ECharacterType::SideScrolling:
		return FText::FromString(TEXT("Side Scrolling Hero"));
	case ECharacterType::Platforming:
		return FText::FromString(TEXT("Platforming Master"));
	case ECharacterType::Combat:
		return FText::FromString(TEXT("Combat Warrior"));
	default:
		return FText::FromString(TEXT("Unknown Character"));
	}
}

FText UCharacterSelectionWidget::GetCharacterDescription(ECharacterType CharacterType) const
{
	switch (CharacterType)
	{
	case ECharacterType::SideScrolling:
		return FText::FromString(TEXT("Perfect for classic side-scrolling adventures.\nFeatures: Wall Jumping, Double Jump, Platform Interaction"));
	case ECharacterType::Platforming:
		return FText::FromString(TEXT("Enhanced platforming with advanced movement.\nFeatures: Dashing, Advanced Jumping, Precise Controls"));
	case ECharacterType::Combat:
		return FText::FromString(TEXT("Melee combat specialist with full combat system.\nFeatures: Combo Attacks, Charged Attacks, Health System"));
	default:
		return FText::FromString(TEXT("No description available."));
	}
}

void UCharacterSelectionWidget::UpdateButtonHighlight()
{
	// Reset all button styles to normal
	if (SideScrollingButton)
	{
		SideScrollingButton->SetBackgroundColor(CurrentSelection == ECharacterType::SideScrolling ? 
			FLinearColor::Yellow : FLinearColor::White);
	}

	if (PlatformingButton)
	{
		PlatformingButton->SetBackgroundColor(CurrentSelection == ECharacterType::Platforming ? 
			FLinearColor::Yellow : FLinearColor::White);
	}

	if (CombatButton)
	{
		CombatButton->SetBackgroundColor(CurrentSelection == ECharacterType::Combat ? 
			FLinearColor::Yellow : FLinearColor::White);
	}
} 