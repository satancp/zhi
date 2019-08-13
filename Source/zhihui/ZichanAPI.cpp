// Fill out your copyright notice in the Description page of Project Settings.


#include "ZichanAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include <time.h>

void UZichanAPI::auth()
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("username"), "chn");
	JsonObject->SetStringField(TEXT("password"), "chn");
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:8080/auth");
	HttpReuest->SetVerb(TEXT("POST"));
	HttpReuest->SetHeader("Content-Type", "application/json");
	HttpReuest->SetContentAsString(OutputString);
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UZichanAPI::authResponse);
	HttpReuest->ProcessRequest();
}

void UZichanAPI::authResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			FString token = JsonObject->GetStringField("token");
			time_t current = time(NULL);
			this->token = token;
			this->tokenActTime = current;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(token));
		}
	}
}

bool UZichanAPI::isTokenValid()
{
	time_t current = time(NULL);
	if (difftime(this->tokenActTime, current) >= 4233600) {
		return false;
	}
	else {
		return true;
	}
}

void UZichanAPI::getStatOnline()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:8080/api/asset/stat/online");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + this->token));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UZichanAPI::getStatOnlineResponse);
	HttpReuest->ProcessRequest();
}

void UZichanAPI::getStatOnlineResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonValue> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> raw = JsonObject->AsArray();
			TArray<FUStatOnline> data;
			for (int32 index = 0; index < raw.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = raw[index]->AsObject();
				int32 oid = single->GetIntegerField("oid");
				FString month = single->GetStringField("month");
				int32 count = single->GetIntegerField("count");
				FString statDate = single->GetStringField("statDate");
				FUStatOnline temp = FUStatOnline(oid, month, count, statDate);
				data.Add(temp);
			}
		}
	}
}

void UZichanAPI::getStatPercentage()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:8080/api/asset/stat/percentage");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + this->token));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UZichanAPI::getStatPercentageResponse);
	HttpReuest->ProcessRequest();
}

void UZichanAPI::getStatPercentageResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonValue> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> raw = JsonObject->AsArray();
			TArray<FUStatPercentage> data;
			for (int32 index = 0; index < raw.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = raw[index]->AsObject();
				FString type = single->GetStringField("type");
				int32 count = single->GetIntegerField("count");
				FUStatPercentage temp = FUStatPercentage(type, count);
				data.Add(temp);
			}
		}
	}
}

void UZichanAPI::getStatStatus()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:8080/api/asset/stat/status");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + this->token));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UZichanAPI::getStatStatusResponse);
	HttpReuest->ProcessRequest();
}

void UZichanAPI::getStatStatusResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonValue> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> raw = JsonObject->AsArray();
			TArray<FUStatStatus> data;
			for (int32 index = 0; index < raw.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = raw[index]->AsObject();
				FString type = single->GetStringField("type");
				int32 count = single->GetIntegerField("count");
				FUStatStatus temp = FUStatStatus(type, count);
				data.Add(temp);
			}
		}
	}
}

void UZichanAPI::getStatType()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:8080/api/asset/stat/type");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + this->token));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UZichanAPI::getStatTypeResponse);
	HttpReuest->ProcessRequest();
}

void UZichanAPI::getStatTypeResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonValue> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> raw = JsonObject->AsArray();
			TArray<FUStatType> data;
			for (int32 index = 0; index < raw.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = raw[index]->AsObject();
				FString type = single->GetStringField("type");
				TArray<TSharedPtr<FJsonValue>> rawSub = single->GetArrayField("subTypes");
				TArray<FString> subTypes;
				for (int32 index2 = 0; index2 < rawSub.Num(); index2++)
				{
					subTypes.Add(rawSub[index2]->AsString());
				}
				FUStatType temp = FUStatType(type, subTypes);
				data.Add(temp);
			}
		}
	}
}

void UZichanAPI::getMaintain()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:8080/api/asset/maintain");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->SetHeader(TEXT("Authorization"), TEXT("Bearer " + this->token));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UZichanAPI::getMaintainResponse);
	HttpReuest->ProcessRequest();
}

void UZichanAPI::getMaintainResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		TSharedPtr<FJsonValue> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			TArray<TSharedPtr<FJsonValue>> raw = JsonObject->AsArray();
			TArray<FUMaintain> data;
			for (int32 index = 0; index < raw.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = raw[index]->AsObject();
				int32 oid = single->GetIntegerField("oid");
				FString type = single->GetStringField("type");
				FString region = single->GetStringField("region");
				FString maintenance = single->GetStringField("maintenance");
				FString planTime = single->GetStringField("planTime");
				FString description = single->GetStringField("description");
				FUMaintain temp = FUMaintain(oid, type, region, maintenance, planTime, description);
				data.Add(temp);
			}
		}
	}
}