// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfCharacter.h"
#include "lab5Character.h"
#include "DwarfAIController.h"

// Sets default values
ADwarfCharacter::ADwarfCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//This specifies that if a DwarfCharacter is placed into the level, by default you want it to use the DwarfAIController
	AIControllerClass = ADwarfAIController::StaticClass();

}

// Called when the game starts or when spawned
void ADwarfCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADwarfCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADwarfCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ADwarfCharacter::StartAttack()
{
	float duration = PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ADwarfCharacter::PlayerTakeDamage, duration, true);
}

void ADwarfCharacter::StopAttack()
{
	StopAnimMontage(AttackAnim);
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

float ADwarfCharacter::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{

	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		if (Health <= 0.0f)
		{
			// We're dead, don't allow further damage
			bCanBeDamaged = false;
			// TODO: Process death
			StopAttack();
			float duration = PlayAnimMontage(DeathAnim);
			ADwarfAIController* dwarfController = Cast<ADwarfAIController>(GetController());
			dwarfController->SetDead();
			GetController()->UnPossess();
			GetWorldTimerManager().SetTimer(OnDeathTimer, this, &ADwarfCharacter::RemoveDwarf, duration - 0.25f, true);
		}
	}
	return ActualDamage;
}

void ADwarfCharacter::RemoveDwarf()
{
	Destroy();
}

void ADwarfCharacter::PlayerTakeDamage()
{
	Alab5Character* playerPawn = Cast<Alab5Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	playerPawn->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
}
