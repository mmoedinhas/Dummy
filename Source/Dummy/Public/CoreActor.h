// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreActorInfo.h"
#include "GameFramework/Actor.h"
#include "CoreActor.generated.h"

UCLASS(BlueprintType)
class DUMMY_API ACoreActor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCoreActorInfo* ActorInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, AActor*> ChildActors;
	
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	virtual void BeginPlay() override;

private:
	void ConstructChildActors();
	void PopulateChildActors();
	void Update();
	
	FDelegateHandle OnActorInfoChangedDelegate;
	void OnActorInfoChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);
};
