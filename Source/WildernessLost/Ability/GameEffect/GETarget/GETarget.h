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

	/** BlueprintNativeEvent��ʾ�ú���Ҫ����ͼ��ʵ�ָ��ǣ�������Ҳ��ʵ�֣����ǲ���ֱ��ʵ���������������ʵ��һ����Ϊ[FunctionName]_Implementation�ĺ�������*/
	UFUNCTION(BlueprintNativeEvent)
	FGameplayAbilityTargetDataHandle GetTargets(AActor* Owner);

};


/** GameplayEffectĿ��������ӵ���� */
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



/** ��������*/
UCLASS()
class WILDERNESSLOST_API UGETarget_Sphere : public UGETarget
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	UGETarget_Sphere() {}

	/** Uses the passed in event data */
	FGameplayAbilityTargetDataHandle GetTargets_Implementation(AActor* Owner);

protected:

	UPROPERTY(EditAnywhere, Category = Ability)
	FVector			offset;		// ���ƫ��ֵ

	UPROPERTY(EditAnywhere, Category = Ability)
	float			radius;		// �뾶

	UPROPERTY(EditAnywhere, Category = Ability)
	TArray<TEnumAsByte<EObjectTypeQuery> > objectTypes;		// ���Ҷ�������

};