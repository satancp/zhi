// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Http.h"
#include "Json.h"
#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "FHuolifenxiAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API AFHuolifenxiAPI : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	void getKeysToday(char type);
	void getKeysTodayResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};
