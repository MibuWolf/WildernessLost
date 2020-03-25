// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilityAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API UAbilityAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);
	
public:

	UPROPERTY(EditAnywhere, Category = Ability)
	FGameplayTag				GameplayTag;		// ����Ability�¼�

	FGameplayEventData			Payload;			// �¼�����

};
