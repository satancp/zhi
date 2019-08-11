// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "HeimingdanAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UHeimingdanAPI : public UObject
{
	GENERATED_BODY()
public:
	UHeimingdanAPI();
	UFUNCTION(BlueprintCallable)
		void getAreaBlackList(FString num);
	void getAreaBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getBlackList(int32 eventType, int32 eventStatus, int32 currPage, int32 pageSize);
	void getBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getBlack();
	void getBlackResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getBlackDetail(FString eventCode);
	void getBlackDetailResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

};

USTRUCT()
struct FUAreaBlackListR {
	GENERATED_BODY()
		UPROPERTY() FString zoneId;
	UPROPERTY() FString zoneName;
	UPROPERTY() int32 eventCount;
	UPROPERTY() int32 flowCount;
	UPROPERTY() FString density;

	FUAreaBlackListR() {};
	FUAreaBlackListR(FString id, FString name, int32 count1, int32 count2, FString den) {
		zoneId = id;
		zoneName = name;
		eventCount = count1;
		flowCount = count2;
		density = den;
	};
};

USTRUCT()
struct FUBlack {
	GENERATED_BODY()
		UPROPERTY() int32 currPage;
	UPROPERTY() int32 pageSize;
	UPROPERTY() int32 rowCount;
	UPROPERTY() int32 pageCount;
	USTRUCT() TArray<FUBlackList> eventList;

	FUBlack() {};
	FUBlack(int32 cp, int32 ps, int32 rc, int32 pc, TArray<FUBlackList> el) {
		currPage = cp;
		pageSize = ps;
		rowCount = rc;
		pageCount = pc;
		eventList = el;
	};
};

USTRUCT()
struct FUBlackList {
	GENERATED_BODY()
		UPROPERTY() FString eventCode;
	UPROPERTY() FString eventName;
	UPROPERTY() FString eventType;
	UPROPERTY() FString eventImageNet;
	UPROPERTY() FString eventStatus;
	UPROPERTY() FString happenTime;
	UPROPERTY() FString crtAddr;
	UPROPERTY() FString eventImage;
	UPROPERTY() FString reason;
	UPROPERTY() FString zoneName;
	UPROPERTY() FString personId;
	UPROPERTY() FString personName;
	UPROPERTY() FString personFaceImage;
	UPROPERTY() FString deviceId;
	UPROPERTY() FString updTime;

	FUBlackList() {};
	FUBlackList(FString ec, FString en, FString et, FString ein, FString es, FString ht, FString ca, FString ei, FString rea, FString zn, FString pi, FString pn, FString pfi, FString di, FString ut) {
		eventCode = ec;
		eventName = en;
		eventType = et;
		eventImageNet = ein;
		eventStatus = es;
		happenTime = ht;
		crtAddr = ca;
		eventImage = ei;
		reason = rea;
		zoneName = zn;
		personId = pi;
		personName = pn;
		personFaceImage = pfi;
		deviceId = di;
		updTime = ut;
	};
};

USTRUCT()
struct FUBlackDetail {
	GENERATED_BODY()
		UPROPERTY() FString eventCode;
	UPROPERTY() FString eventName;
	UPROPERTY() FString sex;
	UPROPERTY() FString age;
	UPROPERTY() FString crtAddr;
	UPROPERTY() int64 crtTime;
	UPROPERTY() FString reason;
	UPROPERTY() FString zoneName;
	UPROPERTY() FString personId;
	UPROPERTY() FString personName;
	UPROPERTY() FString personFaceImage;
	UPROPERTY() FString deviceId;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;

	FUBlackDetail() {};
	FUBlackDetail(FString ec, FString en, FString s, FString a, FString ca, int64 ct, FString r, FString zn, FString pi, FString pn, FString pfi, FString di, FString lon, FString lat, FString dx, FString dy) {
		eventCode = ec;
		eventName = en;
		sex = s;
		age = a;
		crtAddr = ca;
		crtTime = ct;
		reason = r;
		zoneName = zn;
		personId = pi;
		personName = pn;
		personFaceImage = pfi;
		deviceId = di;
		longitude = lon;
		latitude = lat;
		deviceX = dx;
		deviceY = dy;
	};
};