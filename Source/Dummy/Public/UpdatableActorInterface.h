// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpdatableActorInterface.generated.h"

UINTERFACE(MinimalAPI)
class UUpdatableActorInterface : public UInterface
{
	GENERATED_BODY()
};

class DUMMY_API IUpdatableActorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPropertyValue(FName DataName, float Value);
};
