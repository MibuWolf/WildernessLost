// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility.h"

UGameAbility::UGameAbility()
	:Super()
	, AbilityID(0)
	, AutoGive(true)
{
	// 定义不可以激活Ability的Tags 状态Tag死亡 BUFFTag眩晕
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Buff.Stun")));
}

void  UGameAbility::SetAbilityID(int32 abilityID)
{
	AbilityID = abilityID;
}

int32 UGameAbility::GetAbilityID()
{
	return AbilityID;
}

bool  UGameAbility::CanAutoGive()
{
	return AutoGive;
}

void UGameAbility::ApplyGEGroupByTag(FGameplayTag GETag)
{
	FGameEffectGroup* GEGroup = GEGroupMap.Find(GETag);
	AActor* OwningActor = GetOwningActorFromActorInfo();

	if (GEGroup == nullptr || OwningActor == nullptr)
		return;

	if (GEGroup->TargetType.Get() == nullptr)
		return;

	UGETarget* TargetType = GEGroup->TargetType.GetDefaultObject();
	FGameplayAbilityTargetDataHandle targetHandle = TargetType->GetTargets(OwningActor);

	if (targetHandle.Num ()<= 0)
		return;

	for (const TSubclassOf<UGameplayEffect> & GameEffect : GEGroup->GameEffectList)
	{
		BP_ApplyGameplayEffectToTarget(targetHandle, GameEffect);
	}
}
