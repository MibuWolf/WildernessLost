// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "ObjectAttribute.generated.h"


// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API UObjectAttribute : public UAttributeSet
{
	GENERATED_BODY()
public:

	// Constructor and overrides
	UObjectAttribute();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	/** 当前血量 */
	UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_HP)
	FGameplayAttributeData HP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, HP)

	/** 最大血量 */
	UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_MaxHP)
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MaxHp)

	/** 当前蓝量 */
	UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_MP)
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MP)

	/** 最大蓝量 */
	UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_MaxMP)
	FGameplayAttributeData MaxMp;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, MaxMp)

	/** 攻击力 */
	UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, Attack)

	/** 防御力 */
	UPROPERTY(BlueprintReadOnly, Category = "ObjectAttribute", ReplicatedUsing = OnRep_Defense)
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UObjectAttribute, Defense)

protected:

	UFUNCTION()
	virtual void OnRep_HP();

	UFUNCTION()
	virtual void OnRep_MaxHP();

	UFUNCTION()
	virtual void OnRep_MP();

	UFUNCTION()
	virtual void OnRep_MaxMP();

	UFUNCTION()
	virtual void OnRep_Attack();

	UFUNCTION()
	virtual void OnRep_Defense();

};
