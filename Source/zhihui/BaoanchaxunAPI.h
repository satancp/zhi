// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "BaoanchaxunAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UBaoanchaxunAPI : public UObject
{
	GENERATED_BODY()
public:
	UBaoanchaxunAPI();
	UFUNCTION(BlueprintCallable)
		void getDanrenxinxi(FString pid);
	void getDanrenxinxiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getQuanbuxinxi();
	void getQuanbuxinxiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getXingdongguiji(FString pid);
	void getXingdongguijiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getFujinbaoan(FString ecode);
	 void getFujinbaoanResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getPaifabaoan(FString ecode);
		void getPaifabaoanResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FUDanrenxinxi {
	GENERATED_BODY()
		UPROPERTY() FString personId;
	UPROPERTY() FString personFaceImage;
	UPROPERTY() FString personName;
	UPROPERTY() FString zoneName;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;

	FUDanrenxinxi() {};
	FUDanrenxinxi(FString pid, FString pfi, FString pn, FString zn, FString lon, FString lat) {
		personId = pid;
		personFaceImage = pfi;
		personName = pn;
		zoneName = zn;
		longitude = lon;
		latitude = lat;
	};
};

USTRUCT()
struct FUXingdongguiji {
	GENERATED_BODY()
		UPROPERTY() FString personId;
	UPROPERTY() FString deviceId;
	UPROPERTY() FString deviceName;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;
	UPROPERTY() int64 crtTime;

	FUXingdongguiji() {};
	FUXingdongguiji(FString pid, FString di, FString dn, FString dx, FString dy, FString lon, FString lat, int64 ct) {
		personId = pid;
		deviceId = di;
		deviceName = dn;
		deviceX = dx;
		deviceY = dy;
		longitude = lon;
		latitude = lat;
		crtTime = ct;
	};
};

USTRUCT()
struct FUFujinbaoan {
	GENERATED_BODY()
		UPROPERTY() FString personId;
	UPROPERTY() FString personFaceImage;
	UPROPERTY() FString personFaceImageNet;
	UPROPERTY() FString personName;
	UPROPERTY() FString zoneName;
	UPROPERTY() int32 age;
	UPROPERTY() FString distance;

	FUFujinbaoan() {};
	FUFujinbaoan(FString pid, FString pfi, FString pfin, FString pn, FString zn, int32 a, FString di) {
		personId = pid;
		personFaceImage = pfi;
		personFaceImageNet = pfin;
		personName = pn;
		zoneName = zn;
		age = a;
		distance = di;
	};
};