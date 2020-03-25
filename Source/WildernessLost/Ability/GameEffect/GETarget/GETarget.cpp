// Fill out your copyright notice in the Description page of Project Settings.


#include "GETarget.h"

FGameplayAbilityTargetDataHandle UGETarget::GetTargets_Implementation(AActor* Owner)
{
	return FGameplayAbilityTargetDataHandle();
}

FGameplayAbilityTargetDataHandle UGETarget_AbilityOwner::GetTargets_Implementation(AActor* Owner)
{
	FGameplayAbilityTargetDataHandle targetHandle;

	if (Owner == nullptr)
		return targetHandle;

	FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
	NewData->TargetActorArray.Add(Owner);
	targetHandle.Add(NewData);

	return targetHandle;
}
