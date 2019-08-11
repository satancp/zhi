// Fill out your copyright notice in the Description page of Project Settings.


#include "BaoanchaxunAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UBaoanchaxunAPI::UBaoanchaxunAPI() {

}

void UBaoanchaxunAPI::getDanrenxinxi(FString pid)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/securityStaff/list?personId=" + pid);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UBaoanchaxunAPI::getDanrenxinxiResponse);
	HttpReuest->ProcessRequest();
}

void UBaoanchaxunAPI::getDanrenxinxiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TSharedPtr<FJsonObject> single = JsonObject->GetObjectField("data");
			FString personId = single->GetStringField("personId");
			FString personFaceImage = single->GetStringField("personFaceImage");
			FString personName = single->GetStringField("personName");
			FString zoneName = single->GetStringField("zoneName");
			FString longitude = single->GetStringField("longitude");
			FString latitude = single->GetStringField("latitude");
			FUDanrenxinxi data = FUDanrenxinxi(personId, personFaceImage, personName, zoneName, longitude, latitude);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UBaoanchaxunAPI::getQuanbuxinxi()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/securityStaff/list");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UBaoanchaxunAPI::getQuanbuxinxiResponse);
	HttpReuest->ProcessRequest();
}

void UBaoanchaxunAPI::getQuanbuxinxiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUDanrenxinxi> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> rawSingle = rawData[index]->AsObject();
				FString personId = rawSingle->GetStringField("personId");
				FString personFaceImage = rawSingle->GetStringField("personFaceImage");
				FString personName = rawSingle->GetStringField("personName");
				FString zoneName = rawSingle->GetStringField("zoneName");
				FString longitude = rawSingle->GetStringField("longitude");
				FString latitude = rawSingle->GetStringField("latitude");
				FUDanrenxinxi single = FUDanrenxinxi(personId, personFaceImage, personName, zoneName, longitude, latitude);
				data.Add(single);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UBaoanchaxunAPI::getXingdongguiji(FString pid)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/securityStaff/trajectory?personId=" + pid);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UBaoanchaxunAPI::getXingdongguijiResponse);
	HttpReuest->ProcessRequest();
}

void UBaoanchaxunAPI::getXingdongguijiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUXingdongguiji> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> rawSingle = rawData[index]->AsObject();
				FString personId = rawSingle->GetStringField("personId");
				FString deviceId = rawSingle->GetStringField("deviceId");
				FString deviceName = rawSingle->GetStringField("deviceName");
				FString deviceX = rawSingle->GetStringField("deviceX");
				FString deviceY = rawSingle->GetStringField("deviceY");
				FString longitude = rawSingle->GetStringField("longitude");
				FString latitude = rawSingle->GetStringField("latitude");
				int64 crtTime = rawSingle->GetIntegerField("crtTime");
				FUXingdongguiji single = FUXingdongguiji(personId, deviceId, deviceName, deviceX, deviceY, longitude, latitude, crtTime);
				data.Add(single);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UBaoanchaxunAPI::getFujinbaoan(FString ec)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/securityStaff/nearby?eventCode=" + ec);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UBaoanchaxunAPI::getFujinbaoanResponse);
	HttpReuest->ProcessRequest();
}

void UBaoanchaxunAPI::getFujinbaoanResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUFujinbaoan> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> rawSingle = rawData[index]->AsObject();
				FString personId = rawSingle->GetStringField("personId");
				FString personFaceImage = rawSingle->GetStringField("personFaceImage");
				FString personFaceImageNet = rawSingle->GetStringField("personFaceImageNet");
				FString personName = rawSingle->GetStringField("personName");
				FString zoneName = rawSingle->GetStringField("zoneName");
				int32 age = rawSingle->GetIntegerField("age");
				FString distance = rawSingle->GetStringField("distance");
				FUFujinbaoan single = FUFujinbaoan(personId, personFaceImage, personFaceImageNet, personName, zoneName, age, distance);
				data.Add(single);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UBaoanchaxunAPI::getPaifabaoan(FString ec)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getDeal?eventCode=" + ec);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UBaoanchaxunAPI::getPaifabaoanResponse);
	HttpReuest->ProcessRequest();
}

void UBaoanchaxunAPI::getPaifabaoanResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUFujinbaoan> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> rawSingle = rawData[index]->AsObject();
				FString personId = rawSingle->GetStringField("personId");
				FString personFaceImage = rawSingle->GetStringField("personFaceImage");
				FString personFaceImageNet = rawSingle->GetStringField("personFaceImageNet");
				FString personName = rawSingle->GetStringField("personName");
				FString zoneName = rawSingle->GetStringField("zoneName");
				int32 age = rawSingle->GetIntegerField("age");
				FString distance = rawSingle->GetStringField("distance");
				FUFujinbaoan single = FUFujinbaoan(personId, personFaceImage, personFaceImageNet, personName, zoneName, age, distance);
				data.Add(single);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}