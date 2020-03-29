// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../AbilityInputID.h"
#include "../GameEffect/GameEffectGroup.h"
#include "GameAbility.generated.h"

/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API UGameAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UGameAbility();

	bool				CanAutoGive();

	EAbilityInputID		GetAbilityInputID();

public:

	// ��������
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// ���ؽ�������
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);


protected:

	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);

protected:

	UPROPERTY(EditAnywhere, Category = Ability)
	EAbilityInputID		InputID;		// �󶨰���

	UPROPERTY(EditAnywhere, Category = Ability)
	int32				AbilityID;		// ����ID

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				AutoGive;		// �Ƿ�Ĭ��ӵ�д�����

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TMap<FGameplayTag, FGameEffectGroup> GEGroupMap;	// ����Ч��

	FDelegateHandle		EventHandle;	// GameplayEvent�ص�Handle
};
