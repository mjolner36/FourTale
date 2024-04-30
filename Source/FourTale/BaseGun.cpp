// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGun.h"
#include "Components/MeshComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

ABaseGun::ABaseGun()
	: Super()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
	MeshOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshOutline"));
	MeshOutline->SetupAttachment(Mesh);
	
	MuzzleFlashLocation = CreateDefaultSubobject<USphereComponent>(TEXT("MuzzleFlashLocation"));
	MuzzleFlashLocation->SetupAttachment(Mesh);
}
// Sets default values
ABaseGun::ABaseGun(const FObjectInitializer& ObjectInitializer,AShooterCharacter* PlayerRef): Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->PlayerRef = PlayerRef;
}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseGun::PullTrigger()
{
	if (MagazineAmount <= 0) return;
	MagazineAmount--;
	PullTriggerEffect();

	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if(OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	
	OwnerController->GetPlayerViewPoint(Location,Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;
	FHitResult Hit;
	bool IsSuccess = GetWorld()->LineTraceSingleByChannel(Hit,Location,End,ECC_GameTraceChannel1);

	if (IsSuccess)
	{
		FVector ShortDirection = -Rotation.Vector();
		ImpactEffect(Hit.Location,ShortDirection.Rotation());
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(DamageAmount,Hit,ShortDirection,nullptr);
			HitActor->TakeDamage(DamageAmount,DamageEvent,OwnerController,this);
		}
	}
}



