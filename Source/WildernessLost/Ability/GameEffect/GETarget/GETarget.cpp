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


/** Uses the passed in event data */
FGameplayAbilityTargetDataHandle UGETarget_Sphere::GetTargets_Implementation(AActor* Owner)
{
	static const FName SphereTraceMultiName(TEXT("SphereTraceMultiForObjects"));

	// ��ǰ������ײ����
	FCollisionQueryParams Params(SphereTraceMultiName, TStatId(), false, Owner);

	// Ŀ�������ײ����
	TArray<TEnumAsByte<ECollisionChannel>> CollisionObjectTraces;
	CollisionObjectTraces.AddUninitialized(objectTypes.Num());

	for (auto Iter = objectTypes.CreateConstIterator(); Iter; ++Iter)
	{
		CollisionObjectTraces[Iter.GetIndex()] = UEngineTypes::ConvertToCollisionChannel(*Iter);
	}

	FCollisionObjectQueryParams ObjectParams;
	for (auto Iter = CollisionObjectTraces.CreateConstIterator(); Iter; ++Iter)
	{
		const ECollisionChannel & Channel = (*Iter);
		if (FCollisionObjectQueryParams::IsValidObjectQuery(Channel))
		{
			ObjectParams.AddObjectTypesToQuery(Channel);
		}
		else
		{
			UE_LOG(LogBlueprintUserMessages, Warning, TEXT("%d isn't valid object type"), (int32)Channel);
		}
	}

	FGameplayAbilityTargetDataHandle targetHandle;

	if (Owner == nullptr || !ObjectParams.IsValid())
		return targetHandle;

	UWorld* World = Owner->GetWorld();
	TArray<FHitResult> OutHits;
	FVector pos = Owner->GetActorLocation();
	FVector fornt = Owner->GetActorForwardVector();
	bool const bHit = World ? World->SweepMultiByObjectType(OutHits, pos, pos+ fornt, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(radius), Params) : false;

	if (!bHit)
		return targetHandle;

	FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();

	for (auto& hitResult : OutHits)
	{
		NewData->TargetActorArray.Add(hitResult.Actor);
	}

	targetHandle.Add(NewData);

	return targetHandle;
}