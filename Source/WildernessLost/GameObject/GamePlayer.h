// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "../PlayerController/GamePlayerController.h"
#include "GamePlayer.generated.h"

/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API AGamePlayer : public AGameObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGamePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void StopJumping();

	// ��ʼ����
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* hitComponet, AActor* otherActor, UPrimitiveComponent* otherComponet,
			int32 otherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent*		springArm;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent*			camera;

};
