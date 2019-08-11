// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "QitaAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UQitaAPI : public UObject
{
	GENERATED_BODY()
public:
	UQitaAPI();
	UFUNCTION(BlueprintCallable)
		void getXiaoxi(int32 currPage, int32 pageSize, FString seachValue, int32 status);
	void getXiaoxiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getTianqi();
	void getTianqiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FUXiaoxi {
	GENERATED_BODY()
		UPROPERTY() int32 currPage;
	UPROPERTY() int32 pageSize;
	UPROPERTY() int32 rowCount;
	UPROPERTY() int32 pageCount;
	USTRUCT() TArray<FUXiaoxiSingle> messageList;

	FUXiaoxi() {};
	FUXiaoxi(int32 cp, int32 ps, int32 rc, int32 pc, TArray<FUXiaoxiSingle> ml) {
		currPage = cp;
		pageSize = ps;
		rowCount = rc;
		pageCount = pc;
		messageList = ml;
	};
};

USTRUCT()
struct FUXiaoxiSingle {
	GENERATED_BODY()
		UPROPERTY() int32 msgId;
	UPROPERTY() FString userName;
	UPROPERTY() FString content;
	UPROPERTY() FString crtTime;
	UPROPERTY() TArray<FString> imagesUrl;

	FUXiaoxiSingle() {};
	FUXiaoxiSingle(int32 mid, FString name, FString con, FString ctime, TArray<FString> iurls) {
		msgId = mid;
		userName = name;
		content = con;
		crtTime = ctime;
		imagesUrl = iurls;
	};
};

USTRUCT()
struct FUTianqi {
	GENERATED_BODY()
		UPROPERTY() FString temperature;
	UPROPERTY() FString weather;
	UPROPERTY() FString weather_id_fa;
	UPROPERTY() FString weather_id_fb;
	UPROPERTY() FString wind;
	UPROPERTY() FString week;
	UPROPERTY() FString city;
	UPROPERTY() FString date_y;
	UPROPERTY() FString dressing_index;
	UPROPERTY() FString dressing_advice;
	UPROPERTY() FString uv_index;
	UPROPERTY() FString comfort_index;
	UPROPERTY() FString wash_index;
	UPROPERTY() FString travel_index;
	UPROPERTY() FString exercise_index;
	UPROPERTY() FString aqi;
	UPROPERTY() FString quality;

	FUTianqi() {};
	FUTianqi(FString tem, FString wea, FString weafa, FString weafb, FString win, FString wee, FString cit, FString dat, FString drindex, FString dradvice, FString uvindex, FString cindex, FString windex, FString tindex, FString eindex, FString aq, FString qua) {
		temperature = tem;
		weather = wea;
		weather_id_fa = weafa;
		weather_id_fb = weafb;
		wind = win;
		week = wee;
		city = cit;
		date_y = dat;
		dressing_index = drindex;
		dressing_advice = dradvice;
		uv_index = uvindex;
		comfort_index = cindex;
		wash_index = windex;
		travel_index = tindex;
		exercise_index = eindex;
		aqi = aq;
		quality = qua;
	};
};