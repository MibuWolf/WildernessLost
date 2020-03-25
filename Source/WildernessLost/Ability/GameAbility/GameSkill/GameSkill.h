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

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Ability)
	//TMap<FGameplayTag, FGameEffectGroup> GEGroupMap;	// 所有效果
};
