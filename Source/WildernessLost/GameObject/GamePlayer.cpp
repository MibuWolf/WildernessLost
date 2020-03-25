// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayer.h"
#include "../Ability/AbilityInputID.h"

// Sets default values
AGamePlayer::AGamePlayer()
	:Super()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Ĭ�ϰ���������������������/�����ǣ�
	// ����ӦControl����ת����ת��CharacterMovement����
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;

	// ���ý�ɫ�ƶ�����ƶ���ת��ز���
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	// �������ֱ����
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	springArm->SetupAttachment(RootComponent);
	springArm->TargetArmLength = 300.0f;
	springArm->SocketOffset.Z = 50.0f;
	springArm->bUsePawnControlRotation = true;

	// ���������
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
	camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	// ע���������ǽ���ص�
	UCapsuleComponent* pCapsule = GetCapsuleComponent();

	if (pCapsule != nullptr)
	{
		pCapsule->OnComponentBeginOverlap.AddDynamic(this, &AGamePlayer::OnBeginOverlap);
	}

	AGamePlayerController *playerController = Cast <AGamePlayerController>(GetController());

	if (playerController != nullptr)
	{
		playerController->SetActionOperationMode(true);
	}
}

// Called every frame
void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	AbilitySystemComponent->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
		FString("CancelTarget"), FString("EAbilityInputID"), static_cast<int32>(EAbilityInputID::Confirm), static_cast<int32>(EAbilityInputID::Cancel)));
}

void AGamePlayer::OnBeginOverlap(UPrimitiveComponent * hitComponet, AActor * otherActor, UPrimitiveComponent * otherComponet, int32 otherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (otherActor == nullptr)
		return;

	if (otherActor->ActorHasTag(TEXT("GameItem")))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collided with GameItem"));
	}
}


