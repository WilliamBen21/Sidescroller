// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterPreviewActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"

ACharacterPreviewActor::ACharacterPreviewActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create root component
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootComponent = RootSceneComponent;

	// Create skeletal mesh components for each character type
	SideScrollingMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SideScrollingMesh"));
	SideScrollingMesh->SetupAttachment(RootComponent);
	SideScrollingMesh->SetVisibility(false);

	PlatformingMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlatformingMesh"));
	PlatformingMesh->SetupAttachment(RootComponent);
	PlatformingMesh->SetVisibility(false);

	CombatMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CombatMesh"));
	CombatMesh->SetupAttachment(RootComponent);
	CombatMesh->SetVisibility(false);

	// Set default values
	CurrentCharacterType = ECharacterType::SideScrolling;
	RotationSpeed = 30.0f; // Degrees per second
	bAutoRotate = true;
}

void ACharacterPreviewActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial character type
	SetCharacterType(CurrentCharacterType);
}

void ACharacterPreviewActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Auto-rotate the character if enabled
	if (bAutoRotate)
	{
		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw += RotationSpeed * DeltaTime;
		SetActorRotation(CurrentRotation);
	}
}

void ACharacterPreviewActor::SetCharacterType(ECharacterType CharacterType)
{
	CurrentCharacterType = CharacterType;
	UpdateVisibleMesh();
}

void ACharacterPreviewActor::UpdateVisibleMesh()
{
	// Hide all meshes first
	SideScrollingMesh->SetVisibility(false);
	PlatformingMesh->SetVisibility(false);
	CombatMesh->SetVisibility(false);

	// Show the appropriate mesh based on character type
	switch (CurrentCharacterType)
	{
	case ECharacterType::SideScrolling:
		SideScrollingMesh->SetVisibility(true);
		break;
	case ECharacterType::Platforming:
		PlatformingMesh->SetVisibility(true);
		break;
	case ECharacterType::Combat:
		CombatMesh->SetVisibility(true);
		break;
	default:
		// Default to side scrolling character
		SideScrollingMesh->SetVisibility(true);
		break;
	}
} 