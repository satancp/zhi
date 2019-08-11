// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "HuolifenxiAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UHuolifenxiAPI : public UObject
{
	GENERATED_BODY()
public:
	UHuolifenxiAPI();
	void getKeysToday(FString type);
	void getKeysTodayResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getEmotionAnalysis(FString type);
	void getEmotionAnalysisResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getImportantAreaMonitor(FString type);
	void getImportantAreaMonitorResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getImportantAreaExceptionAnalysis(FString type);
	void getImportantAreaExceptionAnalysisResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getExceptionHighFrequency(FString type);
	void getExceptionHighFrequencyResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getExceptionCount(FString type);
	void getExceptionCountResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getExceptionRate(FString type);
	void getExceptionRateResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getPeopleNumber(FString type);
	void getPeopleNumberResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getPeopleRate(FString type);
	void getPeopleRateResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	void getAreaBlackList();
	void getAreaBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FUKeyToday {
	GENERATED_BODY()
	UPROPERTY() FString keyName;
	UPROPERTY() int32 keyValue;
	
	FUKeyToday() {};
	FUKeyToday(FString name, int32 value) {
		keyName = name;
		keyValue = value;
	};
};

USTRUCT()
struct FUEmotionAnalysis {
	GENERATED_BODY()
		UPROPERTY() FString emotionName;
	USTRUCT() TArray<FUEmotionAnalysisZone> emotionZoneList;

	FUEmotionAnalysis() {};
	FUEmotionAnalysis(FString name, TArray<FUEmotionAnalysisZone> zone) {
		emotionName = name;
		emotionZoneList = zone;
	};
};

USTRUCT()
struct FUEmotionAnalysisZone {
	GENERATED_BODY()
		UPROPERTY() FString zoneName;
	UPROPERTY() int32 emotionCount;

	FUEmotionAnalysisZone() {};
	FUEmotionAnalysisZone(FString name, int32 count) {
		zoneName = name;
		emotionCount = count;
	};
};

USTRUCT()
struct FUImportantAreaMonitor {
	GENERATED_BODY()
		UPROPERTY() FString zoneName;
	USTRUCT() TArray<FUImportantAreaMonitorTime> monitorTimeList;

	FUImportantAreaMonitor() {};
	FUImportantAreaMonitor(FString name, TArray<FUImportantAreaMonitorTime> list) {
		zoneName = name;
		monitorTimeList = list;
	};
};

USTRUCT()
struct FUImportantAreaMonitorTime {
	GENERATED_BODY()
		UPROPERTY() FString timeName;
	UPROPERTY() int32 eventCount;

	FUImportantAreaMonitorTime() {};
	FUImportantAreaMonitorTime(FString name, int32 count) {
		timeName = name;
		eventCount = count;
	};
};

USTRUCT()
struct FUImportantAreaExceptionAnalysis {
	GENERATED_BODY()
		USTRUCT() TArray<FUImportantAreaExceptionAnalysisZone> zoneList;
	UPROPERTY() FString eventName;
	UPROPERTY() FString eventType;

	FUImportantAreaExceptionAnalysis() {};
	FUImportantAreaExceptionAnalysis(TArray<FUImportantAreaExceptionAnalysisZone> list, FString name, FString type) {
		zoneList = list;
		eventName = name;
		eventType = type;
	};
};

USTRUCT()
struct FUImportantAreaExceptionAnalysisZone {
	GENERATED_BODY()
		UPROPERTY() FString zoneName;
	UPROPERTY() int32 eventCount;

	FUImportantAreaExceptionAnalysisZone() {};
	FUImportantAreaExceptionAnalysisZone(FString name, int32 count) {
		zoneName = name;
		eventCount = count;
	};
};

USTRUCT()
struct FUExceptionHighFrequency {
	GENERATED_BODY()
		UPROPERTY() FString timeZone;
	UPROPERTY() int32 timeValue;

	FUExceptionHighFrequency() {};
	FUExceptionHighFrequency(FString name, int32 value) {
		timeZone = name;
		timeValue = value;
	};
};

USTRUCT()
struct FUExceptionCount {
	GENERATED_BODY()
		UPROPERTY() FString timeName;
	UPROPERTY() int32 eventCount;

	FUExceptionCount() {};
	FUExceptionCount(FString name, int32 value) {
		timeName = name;
		eventCount = value;
	};
};

USTRUCT()
struct FUExceptionRate {
	GENERATED_BODY()
		UPROPERTY() FString eventName;
	UPROPERTY() int32 eventCount;
	UPROPERTY() FString eventType;

	FUExceptionRate() {};
	FUExceptionRate(FString name, int32 value, FString type) {
		eventName = name;
		eventCount = value;
		eventType = type;
	};
};

USTRUCT()
struct FUPeopleNumber {
	GENERATED_BODY()
		UPROPERTY() FString zoneValue;
	UPROPERTY() FString zoneName;

	FUPeopleNumber() {};
	FUPeopleNumber(FString name, FString value) {
		zoneValue = name;
		zoneName = value;
	};
};

USTRUCT()
struct FUPeopleRate {
	GENERATED_BODY()
		USTRUCT() TArray<FUPeopleRateAnalysis> zoneList;
	UPROPERTY() FString crowdType;
	UPROPERTY() FString crowdName;

	FUPeopleRate() {};
	FUPeopleRate(TArray<FUPeopleRateAnalysis> list, FString name, FString type) {
		zoneList = list;
		crowdType = name;
		crowdName = type;
	};
};

USTRUCT()
struct FUPeopleRateAnalysis {
	GENERATED_BODY()
		UPROPERTY() int32 analysisRatio;
	UPROPERTY() FString analysisName;

	FUPeopleRateAnalysis() {};
	FUPeopleRateAnalysis(int32 name, FString count) {
		analysisRatio = name;
		analysisName = count;
	};
};