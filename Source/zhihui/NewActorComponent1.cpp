// Fill out your copyright notice in the Description page of Project Settings.


#include "NewActorComponent1.h"
#include "HuolifenxiAPI.h"
// Sets default values for this component's properties
UNewActorComponent1::UNewActorComponent1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UNewActorComponent1::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("------------------------------------run----------------------------------"));
	auto api = NewObject<UHuolifenxiAPI>();
	api->getKeysToday("1");
	// ...
	
}


// Called every frame
void UNewActorComponent1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

