// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DwarfAIController.generated.h"

/**
 * 
 */
UCLASS()
class LAB5_API ADwarfAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	enum State
	{
		Start,
		Chase,
		Attack,
		Dead
	};
	void Tick(float deltaTime) override;
	void SetRange(float range) { mRange = range; };
	void ChasePlayer();
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
	void SetDead() { mCurrState = Dead; };
private:
	State mCurrState;
	float mRange;
};
