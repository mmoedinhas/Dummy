// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreActor.h"

#include "UpdatableActorInterface.h"


void ACoreActor::Update()
{
	for(auto& [Name, ChildInfo] : ActorInfo->ChildrenInfo)
	{
		const auto ChildActorPtr = ChildActors.Find(Name);
		if(!ChildActorPtr)
		{
			continue;
		}

		const auto ChildActor = *ChildActorPtr;

		ChildActor->GetRootComponent()->SetRelativeLocation(ChildInfo.Location);

		if(ChildActor->Implements<UUpdatableActorInterface>())
		{
			for(const auto& MapOfFloats : ChildInfo.Properties)
			{
				Cast<IUpdatableActorInterface>(ChildActor)->Execute_SetPropertyValue(ChildActor, MapOfFloats.Key, MapOfFloats.Value);
			}
		}
	}
}

void ACoreActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(ActorInfo)
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(OnActorInfoChangedDelegate);
		OnActorInfoChangedDelegate = FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &ACoreActor::OnActorInfoChanged);
	}

	ConstructChildActors();
}

void ACoreActor::BeginPlay()
{
	Super::BeginPlay();

	if(ActorInfo)
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.Remove(OnActorInfoChangedDelegate);
		OnActorInfoChangedDelegate = FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &ACoreActor::OnActorInfoChanged);
	}

	ConstructChildActors();
}

void ACoreActor::ConstructChildActors()
{
	if(!ActorInfo)
	{
		return;
	}

	PopulateChildActors();
	Update();
}

void ACoreActor::PopulateChildActors()
{
	ChildActors.Empty();

	TArray<FName> ChildrenNames;
	ActorInfo->ChildrenInfo.GetKeys(ChildrenNames);
	TArray<AActor*> AllChildActors;
	GetAllChildActors(AllChildActors);

	for(const FName& Name : ChildrenNames)
	{
		for(AActor* Actor : AllChildActors)
		{
			if(Actor->ActorHasTag(Name))
			{
				ChildActors.Add(Name, Actor);
				break;
			}
		}
	}
}

void ACoreActor::OnActorInfoChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent)
{
	if(ObjectBeingModified == ActorInfo)
	{
		Update();
	}
}
