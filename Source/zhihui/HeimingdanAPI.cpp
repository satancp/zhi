// Fill out your copyright notice in the Description page of Project Settings.


#include "HeimingdanAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UHeimingdanAPI::UHeimingdanAPI() {

}

void UHeimingdanAPI::getAreaBlackList(FString num)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getBlackEventRank?showNum=" + num);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHeimingdanAPI::getAreaBlackListResponse);
	HttpReuest->ProcessRequest();
}

void UHeimingdanAPI::getAreaBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString code = JsonObject->GetStringField("code");
			FString msg = JsonObject->GetStringField("msg");
			TArray<FUAreaBlackListR> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> rawSingle = rawData[index]->AsObject();
				FString zoneId = rawSingle->GetStringField("zoneId");
				FString zoneName = rawSingle->GetStringField("zoneName");
				int32 eventCount = rawSingle->GetIntegerField("eventCount");
				int32 flowCount = rawSingle->GetIntegerField("flowCount");
				FString density = rawSingle->GetStringField("density");
				FUAreaBlackListR single = FUAreaBlackListR(zoneId, zoneName, eventCount, flowCount, density);
				data.Add(single);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHeimingdanAPI::getBlackList(int32 eventType, int32 eventStatus, int32 currPage, int32 pageSize)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("eventType"), eventType);
	JsonObject->SetNumberField(TEXT("eventStatus"), eventStatus);
	JsonObject->SetNumberField(TEXT("currPage"), currPage);
	JsonObject->SetNumberField(TEXT("pageSize"), pageSize);
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/baseListByPc");
	HttpReuest->SetVerb(TEXT("POST"));
	HttpReuest->SetHeader("Content-Type", "application/json");
	HttpReuest->SetContentAsString(OutputString);
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHeimingdanAPI::getBlackListResponse);
	HttpReuest->ProcessRequest();
}

void UHeimingdanAPI::getBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString code = JsonObject->GetStringField("code");
			FString msg = JsonObject->GetStringField("msg");
			TArray<FUBlack> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				TArray<TSharedPtr<FJsonValue>> rawEventList = single->GetArrayField("eventList");
				int32 currPage = single->GetIntegerField("currPage");
				int32 pageSize = single->GetIntegerField("pageSize");
				int32 rowCount = single->GetIntegerField("rowCount");
				int32 pageCount = single->GetIntegerField("pageCount");
				TArray<FUBlackList> eventList;
				for (int32 index2 = 0; index2 < rawEventList.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawEventList[index2]->AsObject();
					FString eventCode = single2->GetStringField("eventCode");
					FString eventName = single2->GetStringField("eventName");
					FString eventType = single2->GetStringField("eventType");
					FString eventImageNet = single2->GetStringField("eventImageNet");
					FString eventStatus = single2->GetStringField("eventStatus");
					FString happenTime = single2->GetStringField("happenTime");
					FString crtAddr = single2->GetStringField("crtAddr");
					FString eventImage = single2->GetStringField("eventImage");
					FString reason = single2->GetStringField("reason");
					FString zoneName = single2->GetStringField("zoneName");
					FString personId = single2->GetStringField("personId");
					FString personName = single2->GetStringField("personName");
					FString personFaceImage = single2->GetStringField("personFaceImage");
					FString deviceId = single2->GetStringField("deviceId");
					FString updTime = single2->GetStringField("updTime");
					eventList.Add(FUBlackList(eventCode, eventName, eventType, eventImageNet, eventStatus, happenTime, crtAddr, eventImage, reason, zoneName, personId, personName, personFaceImage, deviceId, updTime));
				}
				data.Add(FUBlack(currPage, pageSize, rowCount, pageCount, eventList));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHeimingdanAPI::getBlack()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/black/getList");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHeimingdanAPI::getBlackResponse);
	HttpReuest->ProcessRequest();
}

void UHeimingdanAPI::getBlackResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString code = JsonObject->GetStringField("code");
			FString msg = JsonObject->GetStringField("msg");
			TArray<FUBlackDetail> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> rawSingle = rawData[index]->AsObject();
				FString eventCode = rawSingle->GetStringField("eventCode");
				FString eventName = rawSingle->GetStringField("eventName");
				FString sex = rawSingle->GetStringField("sex");
				FString age = rawSingle->GetStringField("age");
				FString crtAddr = rawSingle->GetStringField("crtAddr");
				int64 crtTime = rawSingle->GetIntegerField("crtTime");
				FString reason = rawSingle->GetStringField("reason");
				FString zoneName = rawSingle->GetStringField("zoneName");
				FString personId = rawSingle->GetStringField("personId");
				FString personName = rawSingle->GetStringField("personName");
				FString personFaceImage = rawSingle->GetStringField("personFaceImage");
				FString deviceId = rawSingle->GetStringField("deviceId");
				FString longitude = rawSingle->GetStringField("longitude");
				FString latitude = rawSingle->GetStringField("latitude");
				FString deviceX = rawSingle->GetStringField("deviceX");
				FString deviceY = rawSingle->GetStringField("deviceY");
				FUBlackDetail single = FUBlackDetail(eventCode, eventName, sex, age, crtAddr, crtTime, reason, zoneName, personId, personName, personFaceImage, deviceId, longitude, latitude, deviceX, deviceY);
				data.Add(single);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHeimingdanAPI::getBlackDetail(FString eventCode)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/black/getDetail?eventCode=" + eventCode);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHeimingdanAPI::getBlackDetailResponse);
	HttpReuest->ProcessRequest();
}

void UHeimingdanAPI::getBlackDetailResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString code = JsonObject->GetStringField("code");
			FString msg = JsonObject->GetStringField("msg");
			TSharedPtr<FJsonObject> rawSingle = JsonObject->GetObjectField("data");
			FString eventCode = rawSingle->GetStringField("eventCode");
			FString eventName = rawSingle->GetStringField("eventName");
			FString sex = rawSingle->GetStringField("sex");
			FString age = rawSingle->GetStringField("age");
			FString crtAddr = rawSingle->GetStringField("crtAddr");
			int64 crtTime = rawSingle->GetIntegerField("crtTime");
			FString reason = rawSingle->GetStringField("reason");
			FString zoneName = rawSingle->GetStringField("zoneName");
			FString personId = rawSingle->GetStringField("personId");
			FString personName = rawSingle->GetStringField("personName");
			FString personFaceImage = rawSingle->GetStringField("personFaceImage");
			FString deviceId = rawSingle->GetStringField("deviceId");
			FString longitude = rawSingle->GetStringField("longitude");
			FString latitude = rawSingle->GetStringField("latitude");
			FString deviceX = rawSingle->GetStringField("deviceX");
			FString deviceY = rawSingle->GetStringField("deviceY");
			FUBlackDetail data = FUBlackDetail(eventCode, eventName, sex, age, crtAddr, crtTime, reason, zoneName, personId, personName, personFaceImage, deviceId, longitude, latitude, deviceX, deviceY);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

