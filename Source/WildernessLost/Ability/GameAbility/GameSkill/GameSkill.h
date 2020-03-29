// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameAbility.h"
//#include "../../AbilityTask/"
#include "GameSkill.generated.h"

/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API UGameSkill : public UGameAbility
{
	GENERATED_BODY()
	
public:

	UGameSkill();


public:


	// ���ؼ���ܷ���
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// ���ؽ�������
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);


public:

	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);


protected:

	bool StopMontage();

public:

	/**Skill Montage that Skill is playing */
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	UAnimMontage*		MontageToPlay;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	float	PlayRate = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	FName	SectionName;

	bool	IsPlaying = false;
};
