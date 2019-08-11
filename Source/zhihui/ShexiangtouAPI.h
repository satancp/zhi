// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "ShexiangtouAPI.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UShexiangtouAPI : public UObject
{
	GENERATED_BODY()
public:
	UShexiangtouAPI();
	UFUNCTION(BlueprintCallable)
	void getRmtpInfo();
	void getRmtpInfoResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
	void getAllCameras();
	void getAllCamerasResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FURmtpInfo {
	GENERATED_BODY()
		UPROPERTY() int32 id;
	UPROPERTY() FString deviceName;
	UPROPERTY() FString deviceRtmp;
	UPROPERTY() FString deviceTid;
	UPROPERTY() FString deviceType;
	UPROPERTY() FString changeUrl;
	UPROPERTY() FString deviceCid;

	FURmtpInfo() {};
	FURmtpInfo(int32 i, FString name, FString rtmp, FString tid, FString type, FString url, FString cid) {
		id = i;
		deviceName = name;
		deviceRtmp = rtmp;
		deviceTid = tid;
		deviceType = type;
		changeUrl = url;
		deviceCid = cid;
	};
};

USTRUCT()
struct FUAllCameras {
	GENERATED_BODY()
		UPROPERTY() int32 id;
	UPROPERTY() FString deviceId;
	UPROPERTY() FString deviceName;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;
	UPROPERTY() FString zoneId;
	UPROPERTY() FString zoneName;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;
	UPROPERTY() FString rtspUrl;
	UPROPERTY() int32 updTime;

	FUAllCameras() {};
	FUAllCameras(int32 i, FString did, FString name, FString x, FString y, FString zid, FString zname, FString lon, FString lat, FString rtsp, int32 utime) {
		id = i;
		deviceId = did;
		deviceName = name;
		deviceX = x;
		deviceY = y;
		zoneId = zid;
		zoneName = zname;
		longitude = lon;
		latitude = lat;
		rtspUrl = rtsp;
		updTime = utime;
	};
};