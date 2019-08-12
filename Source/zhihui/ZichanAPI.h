// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "ZichanAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UZichanAPI : public UObject
{
	FString token = "";
	void auth();
	void authResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	GENERATED_BODY()
public:
	UZichanAPI() {
		auth();
	};
	UFUNCTION(BlueprintCallable)
		void getStatOnline();
	void getStatOnlineResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getStatPercentage();
	void getStatPercentageResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getStatStatus();
	void getStatStatusResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getStatType();
	void getStatTypeResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getMaintain();
	void getMaintainResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FUStatOnline {
	GENERATED_BODY()
		UPROPERTY() int32 oid;
	UPROPERTY() FString month;
	UPROPERTY() int32 count;
	UPROPERTY() FString statDate;

	FUStatOnline() {};
	FUStatOnline(int32 o, FString m, int32 c, FString sd) {
		oid = o;
		month = m;
		count = c;
		statDate = sd;
	};
};

USTRUCT()
struct FUStatPercentage {
	GENERATED_BODY()
		UPROPERTY() FString type;
	UPROPERTY() int32 count;

	FUStatPercentage() {};
	FUStatPercentage(FString t, int32 c) {
		type = t;
		count = c;
	};
};

USTRUCT()
struct FUStatStatus {
	GENERATED_BODY()
		UPROPERTY() FString type;
	UPROPERTY() int32 count;

	FUStatStatus() {};
	FUStatStatus(FString t, int32 c) {
		type = t;
		count = c;
	};
};

USTRUCT()
struct FUStatType {
	GENERATED_BODY()
		UPROPERTY() FString type;
	UPROPERTY() TArray<FString> subTypes;

	FUStatType() {};
	FUStatType(FString t, TArray<FString> st) {
		type = t;
		subTypes = st;
	};
};

USTRUCT()
struct FUMaintain {
	GENERATED_BODY()
		UPROPERTY() int32 oid;
	UPROPERTY() FString type;
	UPROPERTY() FString region;
	UPROPERTY() FString maintenance;
	UPROPERTY() FString planTime;
	UPROPERTY() FString description;

	FUMaintain() {};
	FUMaintain(int32 o, FString t, FString r, FString m, FString p, FString d) {
		oid = o;
		type = t;
		region = r;
		maintenance = m;
		planTime = p;
		description = d;
	};
};