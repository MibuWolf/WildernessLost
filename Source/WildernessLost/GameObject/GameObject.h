// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../Ability/Attribute/ObjectAttribute.h"
#include "../Ability/GameAbilitySystemComponent.h"
#include "GameObject.generated.h"

UCLASS()
class WILDERNESSLOST_API AGameObject : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Implement IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

public:

	// 获取动作表现朝向
	UFUNCTION(BlueprintCallable,  Category = Character)
	FVector		GetDirction();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionX(float Value);
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionY(float Value);

	// 获取动作表现HP百分比
	UFUNCTION(BlueprintCallable,  Category = Character)
	float		GetHPPercent();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetHPPercent(float Value);

	// 获取动作表现BUFF移动限制
	UFUNCTION(BlueprintCallable,  Category = Character)
	int32		GetBuffNoMove();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetBuffNoMove(int32 Value);

	// 是否正在释放技能
	UFUNCTION(BlueprintCallable, Category = Character)
	bool		IsInSkill();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetInSkill(bool Value);

protected:

	/** 能力系统 */
	UPROPERTY(VisibleAnyWhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**属性*/
	UPROPERTY(VisibleAnyWhere)
	UObjectAttribute*	Attribute;

protected:

	// 用于动作表现的朝向
	FVector		Dirction;
	// 用于动作表现的血量百分比
	float		HPPercent;
	// 用于动作表现的BUFF移动限制
	int32		Buff_NoMove;
	// 当前是否在释放技能
	bool		IsSkill;
};
