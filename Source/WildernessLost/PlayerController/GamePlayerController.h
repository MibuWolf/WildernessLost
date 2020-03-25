// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WILDERNESSLOST_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AGamePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// ������Ҳ�����ʽ(����ģʽ/3Dģʽ)����ģʽ��ָת��������ɫһ��ת����3Dģʽ���ת����Ҽ�һ��ת
	void	SetActionOperationMode(bool isActionMode);

	// ��ȡ��ǰ�Ƿ�ʱ����ģʽ
	bool	GetActionOperationMode();

	// ֡ѭ��
	virtual void PlayerTick(float DeltaTime);


protected:

	virtual void BeginPlayingState();

protected:

	// ע�ᰴ���¼�
	virtual void	SetupInputComponent();

	// ����WASD����
	void	OnMoveForwardEvent(float Value);
	void	OnMoveRightEvent(float Value);

	// ���������ת
	void	OnTurnCameraEvent(float Value);
	void	OnLookUpCameraEvent(float Value);

	// ������
	void	OnCameraWheelEvent(float Value);
	// ����������ɫ����
	void	OnUpdateCameraArmLength(float deltTime);

	// ������갴��
	void	OnRMouseBtnDownEvent();
	void	OnRMouseBtnUpEvent();
	void	OnLMouseBtnDownEvent();

	// �����л�����ģʽ
	void	OnOPChangedEvent();


protected:

	uint32		bActionMode : 1;		// ��ǰ�Ƿ�ʱ��������ģʽ
	uint32		bRMouseBtn : 1;			// ��ǰ����Ҽ��Ƿ���
	uint32		bChangeCaramaArm : 1;	// ��ǰ�Ƿ���Ҫ��������ֱ�
	float		targetCameraLength;		// �ȴ�����������ƽ�����		
};
