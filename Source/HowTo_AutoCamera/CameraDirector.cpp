// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "CameraDirector.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float fTimeBetweenCamChanges = 2.0f;
	const float fSmoothBlendTime = 0.75f;

	fTimeToNextCamChange -= DeltaTime;

	if (fTimeToNextCamChange <= 0.0f)
	{
		fTimeToNextCamChange += fTimeBetweenCamChanges;

		// find the actor that handles control for the local player
		APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

		if (OurPlayerController)
		{
			if ((OurPlayerController->GetViewTarget() != ACamArray[1]) && (ACamArray[1] != nullptr))
			{
				// cut instantly to camera one
				OurPlayerController->SetViewTargetWithBlend(ACamArray[1], fSmoothBlendTime);
			}
			else if ((OurPlayerController->GetViewTarget() != ACamArray[2]) && (ACamArray[2] != nullptr))
			{
				// blend smoothly to camera two
				OurPlayerController->SetViewTargetWithBlend(ACamArray[2], fSmoothBlendTime);
			}
		}
	}
}
