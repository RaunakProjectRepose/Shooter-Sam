// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Get Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (PlayerPawn && Blackboard)
	{
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
	}

}
