// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "CharacterSelectionWidget.h"
#include "CharacterPreviewActor.generated.h"

/**
 * Actor that displays character previews in the selection menu
 * Shows the different character meshes for players to see before selecting
 */
UCLASS()
class MYSIDESCROLL_API ACharacterPreviewActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterPreviewActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	/** Root scene component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* RootSceneComponent;

	/** Skeletal mesh components for different character types */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SideScrollingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* PlatformingMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* CombatMesh;

	/** Current character being displayed */
	UPROPERTY(BlueprintReadOnly, Category = "Preview")
	ECharacterType CurrentCharacterType;

	/** Rotation speed for character preview */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	float RotationSpeed;

	/** Whether to automatically rotate the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Preview")
	bool bAutoRotate;

public:
	/** Set which character type to display */
	UFUNCTION(BlueprintCallable, Category = "Preview")
	void SetCharacterType(ECharacterType CharacterType);

	/** Get the currently displayed character type */
	UFUNCTION(BlueprintCallable, Category = "Preview")
	ECharacterType GetCurrentCharacterType() const { return CurrentCharacterType; }

protected:
	/** Update which mesh is visible */
	void UpdateVisibleMesh();
}; 