// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameAbility/GameAbility.h"
#include "GameAbilitySystemComponent.generated.h"


/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API UGameAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	UGameAbilitySystemComponent();

	// �������п��ܻ�õ������������Զ���������������ӵ����
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		AutoGiveAbilites();

	// ���һ���µ�����(�����id�����������пɻ������֮�����������)
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		TryAddAbility(int32 AbilityID);

	// �Ƴ�һ������(�����id�����������пɻ������֮�����������)
	UFUNCTION(BlueprintCallable, Category = Ability)
	void		TryRemoveAbility(int32 AbilityID);


public:

	virtual void AbilityLocalInputPressed(int32 InputID);

protected:


	// ��ǰ��ɫ���п���ӵ�е�������Ҳ�������MAP�Ǹý�ɫӵ���������󼯺�
	// ���ڸ�Map�е�����������ζ�ŵ�ǰ��ɫ�Ѿ�������GiveAbility(���ܸ���ĳЩ
	// ����������ʹ�õ��ߺ��ӵ�д�������)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	TMap<int32, TSubclassOf<UGameAbility>> AllPossibleAbilities;
	
	// ��ǰ���ж���
	TMap<int32, int32> AbilityComboCount;			// 
};
