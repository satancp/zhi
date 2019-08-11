// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "YanghuAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UYanghuAPI : public UObject
{
	GENERATED_BODY()
public:
	UYanghuAPI();
	UFUNCTION(BlueprintCallable)
	void getAreaBlackList(FString showNum);
	void getAreaBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
	void getCaseSource();
	void getCaseSourceResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
	void getCaseDeal();
	void getCaseDealResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
	void getCaseRatio();
	void getCaseRatioResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
	void getCaseReportRate();
	void getCaseReportRateResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FUAreaBlackList {
	GENERATED_BODY()
		UPROPERTY() FString zoneId;
	UPROPERTY() FString zoneName;
	UPROPERTY() int32 eventCount;
	UPROPERTY() int32 flowCount;
	UPROPERTY() FString density;

	FUAreaBlackList() {};
	FUAreaBlackList(FString id, FString name, int32 count1, int32 count2, FString den) {
		zoneId = id;
		zoneName = name;
		eventCount = count1;
		flowCount = count2;
		density = den;
	};
};

USTRUCT()
struct FUCaseSource {
	GENERATED_BODY()
		UPROPERTY() int32 caseCount;
	UPROPERTY() FString caseSource;

	FUCaseSource() {};
	FUCaseSource(int32 count, FString source) {
		caseCount = count;
		caseSource = source;
	};
};

USTRUCT()
struct FUCaseDeal {
	GENERATED_BODY()
		UPROPERTY() FString source;
	UPROPERTY() int32 caseCount;

	FUCaseDeal() {};
	FUCaseDeal(FString src, int32 count) {
		source = src;
		caseCount = count;
	};
};

USTRUCT()
struct FUCaseRatio {
	GENERATED_BODY()
		UPROPERTY() int32 caseCount;
	UPROPERTY() FString caseSource;

	FUCaseRatio() {};
	FUCaseRatio(int32 count, FString source) {
		caseCount = count;
		caseSource = source;
	};
};

USTRUCT()
struct FUCaseReportRate {
	GENERATED_BODY()
		UPROPERTY() int32 caseCount;
	UPROPERTY() FString caseSource;

	FUCaseReportRate() {};
	FUCaseReportRate(int32 count, FString source) {
		caseCount = count;
		caseSource = source;
	};
};