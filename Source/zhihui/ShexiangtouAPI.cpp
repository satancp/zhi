// Fill out your copyright notice in the Description page of Project Settings.


#include "ShexiangtouAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UShexiangtouAPI::UShexiangtouAPI() {

}

void UShexiangtouAPI::getRmtpInfo()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/rtmp/getList");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UShexiangtouAPI::getRmtpInfoResponse);
	HttpReuest->ProcessRequest();
}

void UShexiangtouAPI::getRmtpInfoResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FURmtpInfo> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FURmtpInfo(single->GetIntegerField("id"), single->GetStringField("deviceName"), single->GetStringField("deviceRtmp"), single->GetStringField("deviceTid"), single->GetStringField("deviceType"), single->GetStringField("changeUrl"), single->GetStringField("deviceCid")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UShexiangtouAPI::getAllCameras()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/device/baseList");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UShexiangtouAPI::getAllCamerasResponse);
	HttpReuest->ProcessRequest();
}

void UShexiangtouAPI::getAllCamerasResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUAllCameras> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUAllCameras(single->GetIntegerField("id"), single->GetStringField("deviceId"), single->GetStringField("deviceName"), single->GetStringField("deviceX"), single->GetStringField("deviceY"), single->GetStringField("zoneId"), single->GetStringField("zoneName"), single->GetStringField("longitude"), single->GetStringField("latitude"), single->GetStringField("rtspUrl"), single->GetIntegerField("updTime")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}