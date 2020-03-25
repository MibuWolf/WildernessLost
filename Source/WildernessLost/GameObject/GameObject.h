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

	// ��ȡ�������ֳ���
	UFUNCTION(BlueprintCallable,  Category = Character)
	FVector		GetDirction();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionX(float Value);
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetDirctionY(float Value);

	// ��ȡ��������HP�ٷֱ�
	UFUNCTION(BlueprintCallable,  Category = Character)
	float		GetHPPercent();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetHPPercent(float Value);

	// ��ȡ��������BUFF�ƶ�����
	UFUNCTION(BlueprintCallable,  Category = Character)
	int32		GetBuffNoMove();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetBuffNoMove(int32 Value);

	// �Ƿ������ͷż���
	UFUNCTION(BlueprintCallable, Category = Character)
	bool		IsInSkill();
	UFUNCTION(BlueprintCallable, Category = Character)
	void		SetInSkill(bool Value);

protected:

	/** ����ϵͳ */
	UPROPERTY(VisibleAnyWhere)
	UGameAbilitySystemComponent* AbilitySystemComponent;

	/**����*/
	UPROPERTY(VisibleAnyWhere)
	UObjectAttribute*	Attribute;

protected:

	// ���ڶ������ֵĳ���
	FVector		Dirction;
	// ���ڶ������ֵ�Ѫ���ٷֱ�
	float		HPPercent;
	// ���ڶ������ֵ�BUFF�ƶ�����
	int32		Buff_NoMove;
	// ��ǰ�Ƿ����ͷż���
	bool		IsSkill;
};
