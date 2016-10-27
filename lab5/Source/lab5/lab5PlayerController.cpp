// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#include "lab5.h"
#include "lab5PlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "lab5Character.h"
Alab5PlayerController::Alab5PlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void Alab5PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	UpdateMouseLook();
	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		//MoveToMouseCursor();
	}
}

void Alab5PlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &Alab5PlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &Alab5PlayerController::MoveRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &Alab5PlayerController::OnStartFire);
	InputComponent->BindAction("Fire", IE_Released, this, &Alab5PlayerController::OnStopFire);
	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &Alab5PlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &Alab5PlayerController::OnSetDestinationReleased);

	// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &Alab5PlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &Alab5PlayerController::MoveToTouchLocation);
}

void Alab5PlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void Alab5PlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void Alab5PlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void Alab5PlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void Alab5PlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void Alab5PlayerController::MoveForward(float Value)
{
	if (Value != 0.0f) 
	{ 
		APawn* pawn = GetPawn(); 
		if (pawn != nullptr) 
		{
			pawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value); 
		} 
	}
}

void Alab5PlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		APawn* pawn = GetPawn();
		if (pawn != nullptr)
		{
			pawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	}
}

void Alab5PlayerController::UpdateMouseLook()
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			FVector vector = Hit.ImpactPoint - pawn->GetActorLocation();
			vector.Z = 0.0f;
			vector.Normalize();
			FRotator rotator = vector.Rotation();
			pawn->SetActorRotation(rotator);
		}
	}
	
}

void Alab5PlayerController::OnStartFire()
{
	APawn* const Pawn = GetPawn();
	if (Pawn != nullptr)
	{
		Alab5Character *player = Cast<Alab5Character>(Pawn);
		player->OnStartFire();
	}
}

void Alab5PlayerController::OnStopFire()
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		Alab5Character *player = Cast<Alab5Character>(Pawn);
		player->OnStopFire();
	}
}
