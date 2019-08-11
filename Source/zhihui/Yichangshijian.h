// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"
#include "UObject/NoExportTypes.h"
#include "Yichangshijian.generated.h"

/**
 * 
 */
UCLASS()
class ZHIHUI_API UYichangshijian : public UObject
{
	GENERATED_BODY()
public:
	UYichangshijian();
	UFUNCTION(BlueprintCallable)
		void getRenliumijiAlert(FString num);
	void getRenliumijiAlertResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getYichangliebiao(int32 eventType, int32 eventStatus, int32 currPage, int32 pageSize, FString beginTime, FString endTime);
	void getYichangliebiaoResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getYichangliebiaoPC(int32 eventType, int32 eventStatus, int32 currPage, int32 pageSize, FString beginTime, FString endTime);
	void getYichangliebiaoPCResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getYichangbaojing(FString eventCode);
	void getYichangbaojingResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getYichangDetail(FString eventCode);
	void getYichangDetailResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getYichangResultDetail(FString eventCode);
	void getYichangResultDetailResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void resolveYichang(FString eventCode, FString type, TArray<FString> personIds);
	void resolveYichangResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
	UFUNCTION(BlueprintCallable)
		void getYichanggaofadi(FString showNum);
	void getYichanggaofadiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);
};

USTRUCT()
struct FURenliumijiAlert {
	GENERATED_BODY()
		UPROPERTY() FString zoneName;
	UPROPERTY() int32 flowNum;
	UPROPERTY() FString density;
	UPROPERTY() int32 eventCount;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;
	UPROPERTY() FString deviceId;

	FURenliumijiAlert() {};
	FURenliumijiAlert(FString name, int32 num, FString den, int32 ec, FString lon, FString lat, FString dx, FString dy, FString di) {
		zoneName = name;
		flowNum = num;
		density = den;
		eventCount = ec;
		longitude = lon;
		latitude = lat;
		deviceX = dx;
		deviceY = dy;
		deviceId = di;
	};
};

USTRUCT()
struct FUYichangliebiao {
	GENERATED_BODY()
		UPROPERTY() int32 currPage;
	UPROPERTY() int32 pageSize;
	UPROPERTY() int32 rowCount;
	UPROPERTY() int32 pageCount;
	USTRUCT() TArray<FUYichangEvent> eventList;

	FUYichangliebiao() {};
	FUYichangliebiao(int32 cp, int32 ps, int32 rc, int32 pc, TArray<FUYichangEvent> el) {
		currPage = cp;
		pageSize = ps;
		rowCount = rc;
		pageCount = pc;
		eventList = el;
	};
};

USTRUCT()
struct FUYichangEvent {
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

	FUYichangEvent() {};
	FUYichangEvent(FString ec, FString en, FString et, FString ein, FString es, FString ht, FString ca, FString ei, FString rea, FString zn, FString pi, FString pn, FString pfi, FString di, FString ut) {
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
struct FUYichangliebiaoPC {
	GENERATED_BODY()
		UPROPERTY() int32 currPage;
	UPROPERTY() int32 pageSize;
	UPROPERTY() int32 rowCount;
	UPROPERTY() int32 pageCount;
	USTRUCT() TArray<FUYichangEventPC> eventList;

	FUYichangliebiaoPC() {};
	FUYichangliebiaoPC(int32 cp, int32 ps, int32 rc, int32 pc, TArray<FUYichangEventPC> el) {
		currPage = cp;
		pageSize = ps;
		rowCount = rc;
		pageCount = pc;
		eventList = el;
	};
};

USTRUCT()
struct FUYichangEventPC {
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

	FUYichangEventPC() {};
	FUYichangEventPC(FString ec, FString en, FString et, FString ein, FString es, FString ht, FString ca, FString ei, FString rea, FString zn, FString pi, FString pn, FString pfi, FString di, FString ut) {
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
struct FUYichangbaojing {
	GENERATED_BODY()
		UPROPERTY() FString eventCode;
	UPROPERTY() FString eventName;
	UPROPERTY() FString eventType;
	UPROPERTY() FString eventStatus;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;
	UPROPERTY() FString deviceId;
	UPROPERTY() FString deviceName;
	UPROPERTY() FString happenTime;
	UPROPERTY() FString crtAddr;
	UPROPERTY() FString eventImage;

	FUYichangbaojing() {};
	FUYichangbaojing(FString ec, FString en, FString et, FString es, FString lon, FString lat, FString dx, FString dy, FString di, FString dn, FString ht, FString ca, FString ei) {
		eventCode = ec;
		eventName = en;
		eventType = et;
		eventStatus = es;
		longitude = lon;
		latitude = lat;
		deviceX = dx;
		deviceY = dy;
		deviceId = di;
		deviceName = dn;
		happenTime = ht;
		crtAddr = ca;
		eventImage = ei;
	};
};

USTRUCT()
struct FUYichangDetail {
	GENERATED_BODY()
		UPROPERTY() FString eventCode;
	UPROPERTY() FString eventName;
	UPROPERTY() FString eventType;
	UPROPERTY() FString eventStatus;
	UPROPERTY() FString happenTime;
	UPROPERTY() FString crtAddr;
	UPROPERTY() FString eventImage;
	UPROPERTY() FString reason;
	UPROPERTY() FString zoneName;
	UPROPERTY() FString personId;
	UPROPERTY() FString personName;
	UPROPERTY() FString personFaceImage;
	UPROPERTY() int32 isNeedSuppor;
	UPROPERTY() FString deviceId;
	UPROPERTY() FString deviceName;
	UPROPERTY() FString handle_unit;
	UPROPERTY() FString finish_date;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;

	FUYichangDetail() {};
	FUYichangDetail(FString ec, FString en, FString et, FString es, FString ht, FString ca, FString ei, FString rea, FString zn, FString pi, FString pn, FString pfi, int32 ins, FString di, FString dn, FString hu, FString fd, FString dx, FString dy) {
		eventCode = ec;
		eventName = en;
		eventType = et;
		eventStatus = es;
		happenTime = ht;
		crtAddr = ca;
		eventImage = ei;
		reason = rea;
		zoneName = zn;
		personId = pi;
		personName = pn;
		personFaceImage = pfi;
		isNeedSuppor = ins;
		deviceId = di;
		deviceName = dn;
		handle_unit = hu;
		finish_date = fd;
		deviceX = dx;
		deviceY = dy;
	};
};

USTRUCT()
struct FUYichangResultDetail {
	GENERATED_BODY()
		UPROPERTY() FString eventCode;
	UPROPERTY() FString eventName;
	UPROPERTY() FString eventStatus;
	UPROPERTY() FString personId;
	UPROPERTY() FString personName;
	UPROPERTY() FString personFaceImage;
	UPROPERTY() FString successDesc;
	UPROPERTY() FString successTime;
	UPROPERTY() TArray<FString> successImage;

	FUYichangResultDetail() {};
	FUYichangResultDetail(FString ec, FString en, FString es, FString pi, FString pn, FString pfi, FString sd, FString st, TArray<FString> si) {
		eventCode = ec;
		eventName = en;
		eventStatus = es;
		personId = pi;
		personName = pn;
		personFaceImage = pfi;
		successDesc = sd;
		successTime = st;
		successImage = si;
	};
};

USTRUCT()
struct FUYichanggaofadi {
	GENERATED_BODY()
		UPROPERTY() FString policeName;
	UPROPERTY() FString policeNum;
	USTRUCT() TArray<FUYichanggaofadiDevice> devices;

	FUYichanggaofadi() {};
	FUYichanggaofadi(FString pna, FString pnu, TArray<FUYichanggaofadiDevice> ds) {
		policeName = pna;
		policeNum = pnu;
		devices = ds;
	};
};

USTRUCT()
struct FUYichanggaofadiDevice {
	GENERATED_BODY()
		UPROPERTY() FString deviceId;
	UPROPERTY() FString deviceName;
	UPROPERTY() FString deviceX;
	UPROPERTY() FString deviceY;
	UPROPERTY() FString zoneName;
	UPROPERTY() FString rtspUrl;
	UPROPERTY() FString longitude;
	UPROPERTY() FString latitude;

	FUYichanggaofadiDevice() {};
	FUYichanggaofadiDevice(FString di, FString dn, FString dx, FString dy, FString zn, FString ru, FString lon, FString lat) {
		deviceId = di;
		deviceName = dn;
		deviceX = dx;
		deviceY = dy;
		zoneName = zn;
		rtspUrl = ru;
		longitude = lon;
		latitude = lat;
	};
};