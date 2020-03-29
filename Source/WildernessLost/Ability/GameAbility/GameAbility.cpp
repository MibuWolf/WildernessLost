// Fill out your copyright notice in the Description page of Project Settings.


#include "GameAbility.h"
#include "AbilitySystemComponent.h"

UGameAbility::UGameAbility()
	:Super()
	, AbilityID(0)
	, AutoGive(true)
{
	// ���岻���Լ���Ability��Tags ״̬Tag���� BUFFTagѣ��
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	//ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Buff.Stun")));
}


bool UGameAbility::CanAutoGive()
{
	return AutoGive;
}

EAbilityInputID UGameAbility::GetAbilityInputID()
{
	return InputID;
}

void UGameAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData * TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	
	FGameplayTagContainer tagContainer;
	for (auto & Pair : GEGroupMap)
	{
		tagContainer.AddTag(Pair.Key);
	}
	EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(tagContainer, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UGameAbility::OnGameplayEvent));
}


void UGameAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo * ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();

	FGameplayTagContainer tagContainer;
	for (auto & Pair : GEGroupMap)
	{
		tagContainer.AddTag(Pair.Key);
	}

	AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(tagContainer, EventHandle);
}


void UGameAbility::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData * Payload)
{
	FGameEffectGroup* GEGroup = GEGroupMap.Find(EventTag);
	AActor* OwningActor = GetOwningActorFromActorInfo();

	if (GEGroup == nullptr || OwningActor == nullptr)
		return;

	if (GEGroup->TargetType.Get() == nullptr)
		return;

	UGETarget* TargetType = GEGroup->TargetType.GetDefaultObject();
	FGameplayAbilityTargetDataHandle targetHandle = TargetType->GetTargets(OwningActor);

	if (targetHandle.Num() <= 0)
		return;

	for (const TSubclassOf<UGameplayEffect> & GameEffect : GEGroup->GameEffectList)
	{
		BP_ApplyGameplayEffectToTarget(targetHandle, GameEffect);
	}
}
