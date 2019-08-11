// Fill out your copyright notice in the Description page of Project Settings.


#include "HuolifenxiAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "CoreMinimal.h"

UHuolifenxiAPI::UHuolifenxiAPI() {

}

void UHuolifenxiAPI::getKeysToday(FString type)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/keys/getList?showNum=10&channel=shuian&type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getKeysTodayResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getKeysTodayResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUKeyToday> data; //[{"keyName": "成人","keyValue" : 2779}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUKeyToday(single->GetStringField("keyName"), single->GetIntegerField("keyValue")));
				UE_LOG(LogTemp, Warning, TEXT("%s"), *(single->GetStringField("keyName")));
				UE_LOG(LogTemp, Warning, TEXT("%s"), *(single->GetStringField("keyValue")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getEmotionAnalysis(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/emotion/getList?channel=shuian&type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getEmotionAnalysisResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getEmotionAnalysisResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUEmotionAnalysis> data; //[{ "emotionName": "微笑", "emotionZoneList": [{"zoneName": "东安路广场","emotionCount" : 0}}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString emotionName = single->GetStringField("emotionName"); // emotionName: 微笑
				TArray<TSharedPtr<FJsonValue>> rawEmotionZoneList = single->GetArrayField("emotionZoneList");
				TArray<FUEmotionAnalysisZone> emotionZoneList; // [{"zoneName": "东安路广场","emotionCount" : 0}}]
				for (int32 index2 = 0; index2 < rawEmotionZoneList.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawEmotionZoneList[index2]->AsObject();
					emotionZoneList.Add(FUEmotionAnalysisZone(single2->GetStringField("zoneName"), single2->GetIntegerField("emotionCount")));
				}
				data.Add(FUEmotionAnalysis(emotionName, emotionZoneList));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getImportantAreaMonitor(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/monitor/getList?channel=shuian&type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getImportantAreaMonitorResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getImportantAreaMonitorResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUImportantAreaMonitor> data; //[{ "zoneName": "东安路广场", "monitorTimeList": [{"timeName": "09:00","eventCount" : 0}}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString zoneName = single->GetStringField("zoneName"); // emotionName: 微笑
				TArray<TSharedPtr<FJsonValue>> rawMonitorTimeList = single->GetArrayField("monitorTimeList");
				TArray<FUImportantAreaMonitorTime> monitorTimeList; // [{"zoneName": "东安路广场","emotionCount" : 0}}]
				for (int32 index2 = 0; index2 < rawMonitorTimeList.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawMonitorTimeList[index2]->AsObject();
					monitorTimeList.Add(FUImportantAreaMonitorTime(single2->GetStringField("timeName"), single2->GetIntegerField("eventCount")));
				}
				data.Add(FUImportantAreaMonitor(zoneName, monitorTimeList));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getImportantAreaExceptionAnalysis(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getZoneEventAnalysis?type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getImportantAreaExceptionAnalysisResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getImportantAreaExceptionAnalysisResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUImportantAreaExceptionAnalysis> data; //[{ "zoneList": [{"zoneName": "东安路广场","eventCount" : 0}, "eventName": "黑名单出现", "eventType": "faceMonitorTriggerEvent"}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				TArray<TSharedPtr<FJsonValue>> rawZoneList = single->GetArrayField("zoneList");
				FString eventName = single->GetStringField("eventName"); // eventName: 黑名单出现
				FString eventType = single->GetStringField("eventType"); // eventType: faceMonitorTriggerEvent
				TArray<FUImportantAreaExceptionAnalysisZone> zoneList; // [{"zoneName": "东安路广场","emotionCount" : 0}}]
				for (int32 index2 = 0; index2 < rawZoneList.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawZoneList[index2]->AsObject();
					zoneList.Add(FUImportantAreaExceptionAnalysisZone(single2->GetStringField("zoneName"), single2->GetIntegerField("eventCount")));
				}
				data.Add(FUImportantAreaExceptionAnalysis(zoneList, eventName, eventType));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getExceptionHighFrequency(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getEventHairTime?type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getExceptionHighFrequencyResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getExceptionHighFrequencyResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUExceptionHighFrequency> data; //[{"timeZone": "0:00-3:00","timeValue" : 2779}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUExceptionHighFrequency(single->GetStringField("timeZone"), single->GetIntegerField("timeValue")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getExceptionCount(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getTodayEventCount?type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getExceptionCountResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getExceptionCountResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUExceptionCount> data; //[{"timeName": "09:00","eventCount" : 0}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUExceptionCount(single->GetStringField("timeName"), single->GetIntegerField("eventCount")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getExceptionRate(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getEventRatio?type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getExceptionRateResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getExceptionRateResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUExceptionRate> data; //[{"eventName": "黑名单出现","eventCount" : 0, "eventType": "faceMonitorTriggerEvent"}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUExceptionRate(single->GetStringField("eventName"), single->GetIntegerField("eventCount"), single->GetStringField("eventType")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getPeopleNumber(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/flow/statistics?channel=shuian&type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getPeopleNumberResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getPeopleNumberResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUPeopleNumber> data; //[{"zoneValue": "140","zoneName" : "13:18"}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				data.Add(FUPeopleNumber(single->GetStringField("zoneValue"), single->GetStringField("zoneName")));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getPeopleRate(FString type) {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getCrowdRatioAnalysis?channel=shuian&type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getPeopleRateResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getPeopleRateResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {
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
			FString code = JsonObject->GetStringField("code"); // code: 0000
			FString msg = JsonObject->GetStringField("msg"); // msg: 成功
			TArray<FUPeopleRate> data; //[{ "analysisList": [{"analysisRatio": 28,"analysisName" : "小孩"}, "crowdType": "allCrowd", "crowdName": "总体占比分析"}]
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				TArray<TSharedPtr<FJsonValue>> rawAnalysisList = single->GetArrayField("analysisList");
				FString crowdType = single->GetStringField("crowdType"); // crowdType: allCrowd
				FString crowdName = single->GetStringField("crowdName"); // crowdName: 总体占比分析
				TArray<FUPeopleRateAnalysis> analysisList; // [{"analysisRatio": 28,"analysisName" : "小孩"}}]
				for (int32 index2 = 0; index2 < rawAnalysisList.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawAnalysisList[index2]->AsObject();
					analysisList.Add(FUPeopleRateAnalysis(single2->GetIntegerField("analysisRatio"), single2->GetStringField("analysisName")));
				}
				data.Add(FUPeopleRate(analysisList, crowdType, crowdName));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UHuolifenxiAPI::getAreaBlackList() {
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/getBlackEventRank?showNum=10");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UHuolifenxiAPI::getAreaBlackListResponse);
	HttpReuest->ProcessRequest();
}

void UHuolifenxiAPI::getAreaBlackListResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded) {

}