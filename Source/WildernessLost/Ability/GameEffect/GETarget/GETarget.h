// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GETarget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WILDERNESSLOST_API UGETarget : public UObject
{
	GENERATED_BODY()
	
public:

	UGETarget() {}

	/** BlueprintNativeEvent表示该函数要在蓝图中实现覆盖，代码中也可实现，但是并非直接实现这个方法名而是实现一个名为[FunctionName]_Implementation的函数主体*/
	UFUNCTION(BlueprintNativeEvent)
	FGameplayAbilityTargetDataHandle GetTargets(AActor* Owner);

};


/** GameplayEffect目标是能力拥有者 */
UCLASS(NotBlueprintable)
class WILDERNESSLOST_API UGETarget_AbilityOwner : public UGETarget
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UGETarget_AbilityOwner() {}

	/** Uses the passed in event data */
	FGameplayAbilityTargetDataHandle GetTargets_Implementation(AActor* Owner);

};