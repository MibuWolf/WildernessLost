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

	UFUNCTION(BlueprintCallable, Category = Ability)
	void		SetAbilityID(int32 abilityID);

	UFUNCTION(BlueprintCallable, Category = Ability)
	int32		GetAbilityID();

	UFUNCTION(BlueprintCallable, Category = Ability)
	bool		CanAutoGive();

	UFUNCTION(BlueprintCallable, Category = Ability)
	void		ApplyGEGroupByTag(FGameplayTag GETag);

public:

	UPROPERTY(EditAnywhere, Category = Ability)
	EAbilityInputID		InputID;		// �󶨰���

protected:

	UPROPERTY(EditAnywhere, Category = Ability)
	int32				AbilityID;		// ����ID

	UPROPERTY(EditAnywhere, Category = Ability)
	bool				AutoGive;		// �Ƿ�Ĭ��ӵ�д�����

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	TMap<FGameplayTag, FGameEffectGroup> GEGroupMap;	// ����Ч��

};
