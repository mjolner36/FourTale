// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterCharacter.h"
#include "Components/SphereComponent.h"
#include "BaseGun.generated.h"

class UNiagaraSystem;

UCLASS()
class FOURTALE_API ABaseGun : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseGun();
	// Sets default values for this actor's properties
	ABaseGun(const FObjectInitializer& ObjectInitializer,AShooterCharacter* PlayerRef);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void PullTrigger();
	
	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName = "Pull Trigger Effect"))
	void PullTriggerEffect();

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName = "Impact Effect"))
	void ImpactEffect(FVector HitLocation,FRotator ShotRotation);

	UPROPERTY(BlueprintReadWrite, Category = "Reference")
	AShooterCharacter* PlayerRef;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Effect")
	USphereComponent* MuzzleFlashLocation;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	UMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere)
	UMeshComponent* MeshOutline;

	UPROPERTY(EditAnywhere,Category="Basic")
	float MaxRange = 1000;
	UPROPERTY(EditAnywhere,Category="Basic")
	float DamageAmount;
	UPROPERTY(EditAnywhere,Category="Basic")
	float MagazineAmount;
};
