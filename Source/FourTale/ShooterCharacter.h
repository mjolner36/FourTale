// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class FOURTALE_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName = "Camera Shake On Move"))
	void CameraShakeOnMove();

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookSide(float AxisValue);
	void MoveSide(float AxisValue);
	void Jumping();
	bool CheckIsMoving() const;
};
