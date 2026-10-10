// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"

#define LOG(x) UE_LOG(LogTemp, Warning, TEXT(x));

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(SceneRoot);

	MuzzleFlashParticleSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("MuzzleFlash"));
	MuzzleFlashParticleSystem->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	MuzzleFlashParticleSystem->Deactivate();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	MuzzleFlashParticleSystem->Activate(true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShootSound, GetActorLocation());

	if (OwnerController)
	{
		FVector ViewPointLocation;
		FRotator ViewPointRotation;
		OwnerController->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);

		FVector EndLocation = ViewPointLocation + ViewPointRotation.Vector() * MaxRange;

		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		bool IsHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			ViewPointLocation,
			EndLocation,
			ECC_GameTraceChannel2, 
			Params
		);
		if (IsHit)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				ImpactParticleSystem,
				HitResult.ImpactPoint,
				HitResult.ImpactPoint.Rotation()
			);

			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);

			AActor* HitActor = HitResult.GetActor();
			if (HitActor) 
			{
				UGameplayStatics::ApplyDamage(
					HitActor,
					BulletDamage,
					OwnerController,
					this,
					UDamageType::StaticClass()
				);
			}
		}
	}
}

