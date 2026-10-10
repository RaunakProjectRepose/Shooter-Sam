// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "ShooterSamCharacter.h"
#include "ShooterAI.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	TArray<AActor*> ShooterAIActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);
		
	/*
	for (int32 LoopIndex = 0; LoopIndex < ShooterAIActors.Num(); LoopIndex++)
	{
		AActor* ShooterAIActor = ShooterAIActors[LoopIndex];
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);

		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
		}
	}
	*/

	for (AActor* ShooterAIActor : ShooterAIActors)
	{
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActor);

		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
		}
	}
}
