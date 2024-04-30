// Fill out your copyright notice in the Description page of Project Settings.
#include "ShooterCharacter.h"
#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	//скрыл weapon mesh c модели
	GetMesh()->HideBoneByName(TEXT("weapon_r"),PBO_None);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"),this,&AShooterCharacter::MoveSide);
	
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this,&AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookSide"),this,&AShooterCharacter::LookSide);
	
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&AShooterCharacter::Jumping);
}

bool AShooterCharacter::CheckIsMoving() const
{
	return GetCharacterMovement()->Velocity.Length() > 0.f;
}
void AShooterCharacter::MoveForward(float AxisValue)
{
	if(!GetCharacterMovement()->IsFalling()) AddMovementInput(GetActorForwardVector() * AxisValue);
	if (CheckIsMoving()) CameraShakeOnMove();
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookSide(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::MoveSide(float AxisValue)
{
	if(!GetCharacterMovement()->IsFalling()) AddMovementInput(GetActorRightVector() * AxisValue);
	if (CheckIsMoving()) CameraShakeOnMove();
}

void AShooterCharacter::Jumping()
{
	Jump();
}
