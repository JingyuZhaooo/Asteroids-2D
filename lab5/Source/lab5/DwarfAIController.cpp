// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfAIController.h"
#include "DwarfCharacter.h"

void ADwarfAIController::BeginPlay()
{
	Super::BeginPlay();
	/*
	APawn* const Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (Pawn != nullptr)
	{
		MoveToActor(Pawn);
	}
	*/
	mCurrState = Start;
	mRange = 150.0f;
}

void ADwarfAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (mCurrState == Start)
	{
		ChasePlayer();
	}
	else if (mCurrState == Attack)
	{
		APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
		ADwarfCharacter* dwarfPawn = Cast<ADwarfCharacter>(GetPawn());
		float dist = FVector::Dist(dwarfPawn->GetActorLocation(), Pawn->GetActorLocation());
		if (dist > 150.0f)
		{
			ChasePlayer();
			dwarfPawn->StopAttack();
		}
	}
}

void ADwarfAIController::ChasePlayer()
{
	APawn* const Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (Pawn != nullptr)
	{
		MoveToActor(Pawn);
		mCurrState = Chase;
	}
}

void ADwarfAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	if (Result == EPathFollowingResult::Success)
	{
		mCurrState = Attack;
		ADwarfCharacter *dwarfPawn = Cast<ADwarfCharacter>(GetPawn());
		if (dwarfPawn != nullptr)
		{

			dwarfPawn->StartAttack();
		}
	}
}