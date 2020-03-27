// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayerController.h"
#include "../GameObject/GamePlayer.h"

AGamePlayerController::AGamePlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), bActionMode(true)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::None;
	targetCameraLength = 0.0f;
	bChangeCaramaArm = false;
}

void AGamePlayerController::SetActionOperationMode(bool isActionMode)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player == nullptr)
		return;

	bActionMode = isActionMode;

	if (bActionMode)
	{
		bShowMouseCursor = false;
		player->bUseControllerRotationYaw = true;
		player->bUseControllerRotationPitch = false;
		player->bUseControllerRotationRoll = false;
		InputYawScale = 2.5f;
	}
	else
	{
		bShowMouseCursor = true;
		player->bUseControllerRotationYaw = false;
		player->bUseControllerRotationPitch = false;
		player->bUseControllerRotationRoll = false;
		InputYawScale = 2.5f;
	}
}

bool AGamePlayerController::GetActionOperationMode()
{
	return bActionMode;
}

void AGamePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	OnUpdateCameraArmLength(DeltaTime);
}

void AGamePlayerController::BeginPlayingState()
{
	Super::BeginPlayingState();
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player != nullptr)
	{
		targetCameraLength = player->springArm->TargetArmLength;

		// ������Ծ
		InputComponent->BindAction("Jump", IE_Pressed, player, &AGamePlayer::Jump);
		InputComponent->BindAction("Jump", IE_Released, player, &AGamePlayer::StopJumping);
	}
}

void AGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent == nullptr)
		return;

	// ʹ�û������ת�������
	InputComponent->BindAxis("Turn", this, &AGamePlayerController::OnTurnCameraEvent);
	InputComponent->BindAxis("LookUp", this, &AGamePlayerController::OnLookUpCameraEvent);

	// �������ǰ�������ƶ�
	InputComponent->BindAxis("MoveForward", this, &AGamePlayerController::OnMoveForwardEvent);
	InputComponent->BindAxis("MoveRight", this, &AGamePlayerController::OnMoveRightEvent);
	InputComponent->BindAxis("MouseWheel", this, &AGamePlayerController::OnCameraWheelEvent);

	// ��갴��
	InputComponent->BindAction("RMouseBtn", IE_Pressed, this, &AGamePlayerController::OnRMouseBtnDownEvent);
	InputComponent->BindAction("RMouseBtn", IE_Released, this, &AGamePlayerController::OnRMouseBtnUpEvent);

	InputComponent->BindAction("LMouseBtn", IE_Pressed, this, &AGamePlayerController::OnLMouseBtnDownEvent);

	// �����л�������ʽ
	InputComponent->BindAction("Alt", IE_Pressed, this, &AGamePlayerController::OnOPChangedEvent);

}

void AGamePlayerController::OnMoveForwardEvent(float Value)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player != nullptr)
	{
		UAbilitySystemComponent* AbilitySystemComponent = player->GetAbilitySystemComponent();

		if (AbilitySystemComponent == nullptr)
			return;

		FGameplayTagContainer tagContainer;
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("State.Dead"));
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("State.Skill"));
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("Buff.NoMove"));
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("Buff.Stun"));

		if (AbilitySystemComponent->HasAnyMatchingGameplayTags(tagContainer))
			return;

		player->SetDirctionY(Value);
		if (Value != 0)
		{
			// �ӵ�ǰ��������ȡ�������Ƕ�
			const FRotator Rotation = player->GetActorRotation();
			// ��XZƽ�淽��
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// ���������ǰ���ƶ�
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			player->AddMovementInput(Direction, Value);
		}
	}
}

void AGamePlayerController::OnMoveRightEvent(float Value)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player != nullptr)
	{
		UAbilitySystemComponent* AbilitySystemComponent = player->GetAbilitySystemComponent();

		if (AbilitySystemComponent == nullptr)
			return;

		FGameplayTagContainer tagContainer;
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("State.Dead"));
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("State.Skill"));
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("Buff.NoMove"));
		//tagContainer.AddTag(FGameplayTag::RequestGameplayTag("Buff.Stun"));

		if (AbilitySystemComponent->HasAnyMatchingGameplayTags(tagContainer))
			return;

		player->SetDirctionX(Value);

		if (Value != 0)
		{
			// �ӵ�ǰ��������ȡ�������Ƕ�
			const FRotator Rotation = player->GetActorRotation();
			// ��XZƽ�淽��
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// ���������ǰ���ƶ�
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			player->AddMovementInput(Direction, Value);
		}
	}
}

void AGamePlayerController::OnTurnCameraEvent(float Value)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player == nullptr)
		return;

	// 3Dģʽ�Ҽ�����ʱ��ת��ɫ�������ת���
	if ( !bActionMode && bRMouseBtn)
	{
		FRotator yaw = player->GetActorRotation();
		yaw.Yaw += Value;
		player->SetActorRotation(yaw);
	}
	else
	{
		player->AddControllerYawInput(Value);
	}
}

void AGamePlayerController::OnLookUpCameraEvent(float Value)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player == nullptr)
		return;

	player->AddControllerPitchInput(Value);
}

void AGamePlayerController::OnCameraWheelEvent(float Value)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player != nullptr && Value != 0)
	{
		float length = player->springArm->TargetArmLength;
		length -= Value * 250;

		if (length <= 100.0f)
			length = 100.0f;

		if (length >= 1500.0f)
			length = 1500.0f;

		targetCameraLength = length;
		bChangeCaramaArm = true;
	}
}

void AGamePlayerController::OnUpdateCameraArmLength(float deltTime)
{
	AGamePlayer* player = Cast<AGamePlayer>(GetPawn());

	if (player == nullptr || !bChangeCaramaArm)
		return;

	if (fabs(player->springArm->TargetArmLength - targetCameraLength) < 10)
		return;

	float speed = 400; // ����ƽ��ٶ�
	if (fabs(targetCameraLength - player->springArm->TargetArmLength) < speed * deltTime)
	{
		bChangeCaramaArm = false;
		player->springArm->TargetArmLength = targetCameraLength;
		return;
	}

	int32 op = (targetCameraLength - player->springArm->TargetArmLength > 0) ? 1 : -1;
	player->springArm->TargetArmLength += op * speed * deltTime;
}

void AGamePlayerController::OnRMouseBtnDownEvent()
{
	bRMouseBtn = true;
}

void AGamePlayerController::OnRMouseBtnUpEvent()
{
	bRMouseBtn = false;
}

void AGamePlayerController::OnLMouseBtnDownEvent()
{
	if (bActionMode)
	{

	}
}


void AGamePlayerController::OnOPChangedEvent()
{
	SetActionOperationMode(!bActionMode);
}

