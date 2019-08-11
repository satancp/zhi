// Fill out your copyright notice in the Description page of Project Settings.


#include "YanghuAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UYanghuAPI::UYanghuAPI() {

}

void UYanghuAPI::getAreaBlackList(FString showNum)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getBlackEventRank?showNum=" + showNum);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYanghuAPI::getAreaBlackListResponse);
	HttpReuest->ProcessRequest();
}

void UYanghuAPI::getAreaBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUAreaBlackList> data; 
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUAreaBlackList(single->GetStringField("zoneId"), single->GetStringField("zoneName"), single->GetIntegerField("eventCount"), single->GetIntegerField("flowCount"), single->GetStringField("density")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYanghuAPI::getCaseSource()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/yanghu/caseSource");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYanghuAPI::getCaseSourceResponse);
	HttpReuest->ProcessRequest();
}

void UYanghuAPI::getCaseSourceResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUCaseSource> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUCaseSource(single->GetIntegerField("caseCount"), single->GetStringField("caseSource")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYanghuAPI::getCaseDeal()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/yanghu/caseDeal");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYanghuAPI::getCaseDealResponse);
	HttpReuest->ProcessRequest();
}

void UYanghuAPI::getCaseDealResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUCaseDeal> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUCaseDeal(single->GetStringField("source"), single->GetIntegerField("caseCount")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYanghuAPI::getCaseRatio()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/yanghu/caseRatio");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYanghuAPI::getCaseRatioResponse);
	HttpReuest->ProcessRequest();
}

void UYanghuAPI::getCaseRatioResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUCaseRatio> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUCaseRatio(single->GetIntegerField("caseCount"), single->GetStringField("caseSource")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYanghuAPI::getCaseReportRate()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/yanghu/caseReportRate");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYanghuAPI::getCaseReportRateResponse);
	HttpReuest->ProcessRequest();
}

void UYanghuAPI::getCaseReportRateResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUCaseReportRate> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUCaseReportRate(single->GetIntegerField("caseCount"), single->GetStringField("caseSource")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}