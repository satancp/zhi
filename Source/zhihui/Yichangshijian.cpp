// Fill out your copyright notice in the Description page of Project Settings.


#include "Yichangshijian.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UYichangshijian::UYichangshijian() {

}

void UYichangshijian::getRenliumijiAlert(FString num)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/flowList?showNum=" + num);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getRenliumijiAlertResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getRenliumijiAlertResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			FURenliumijiAlert data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString zoneName = single->GetStringField("zoneName");
				int32 flowNum = single->GetIntegerField("flowNum");
				FString density = single->GetStringField("density");
				int32 eventCount = single->GetIntegerField("eventCount");
                FString longitude = single->GetStringField("longitude");
                FString latitude = single->GetStringField("latitude");
                FString deviceX = single->GetStringField("deviceX");
                FString deviceY = single->GetStringField("deviceY");
                FString deviceId = single->GetStringField("deviceId");
				data = FURenliumijiAlert(zoneName, flowNum, density, eventCount, longitude, latitude, deviceX, deviceY, deviceId);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::getYichangliebiao(int32 eventType, int32 eventStatus, int32 currPage, int32 pageSize, FString beginTime = "", FString endTime = "")
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("eventType"), eventType);
	JsonObject->SetNumberField(TEXT("eventStatus"), eventStatus);
    JsonObject->SetNumberField(TEXT("currPage"), currPage);
    JsonObject->SetNumberField(TEXT("pageSize"), pageSize);
	if (beginTime != "") {
		JsonObject->SetStringField(TEXT("beginTime"), beginTime);
	}
	if (endTime != "") {
		JsonObject->SetStringField(TEXT("endTime"), endTime);
	}
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/baseList");
	HttpReuest->SetVerb(TEXT("POST"));
	HttpReuest->SetHeader("Content-Type", "application/json");
	HttpReuest->SetContentAsString(OutputString);
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getYichangliebiaoResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getYichangliebiaoResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUYichangliebiao> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				TArray<TSharedPtr<FJsonValue>> rawEventList = single->GetArrayField("eventList");
				int32 currPage = single->GetIntegerField("currPage");
				int32 pageSize = single->GetIntegerField("pageSize");
				int32 rowCount = single->GetIntegerField("rowCount");
				int32 pageCount = single->GetIntegerField("pageCount");
				TArray<FUYichangEvent> eventList;
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
					eventList.Add(FUYichangEvent(eventCode, eventName, eventType, eventImageNet, eventStatus, happenTime, crtAddr, eventImage, reason, zoneName, personId, personName, personFaceImage, deviceId, updTime));
				}
				data.Add(FUYichangliebiao(currPage, pageSize, rowCount, pageCount, eventList));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::getYichangliebiaoPC(int32 eventType, int32 eventStatus, int32 currPage, int32 pageSize, FString beginTime = "", FString endTime = "")
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("eventType"), eventType);
	JsonObject->SetNumberField(TEXT("eventStatus"), eventStatus);
    JsonObject->SetNumberField(TEXT("currPage"), currPage);
    JsonObject->SetNumberField(TEXT("pageSize"), pageSize);
	if (beginTime != "") {
		JsonObject->SetStringField(TEXT("beginTime"), beginTime);
	}
	if (endTime != "") {
		JsonObject->SetStringField(TEXT("endTime"), endTime);
	}
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/baseListByPc");
	HttpReuest->SetVerb(TEXT("POST"));
	HttpReuest->SetHeader("Content-Type", "application/json");
	HttpReuest->SetContentAsString(OutputString);
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getYichangliebiaoPCResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getYichangliebiaoPCResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<TSharedPtr<FJsonValue>> rawEventList = single->GetArrayField("eventList");
			int32 currPage = single->GetIntegerField("currPage");
			int32 pageSize = single->GetIntegerField("pageSize");
			int32 rowCount = single->GetIntegerField("rowCount");
			int32 pageCount = single->GetIntegerField("pageCount");
			TArray<FUYichangEventPC> eventList;
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
				eventList.Add(FUYichangEventPC(eventCode, eventName, eventType, eventImageNet, eventStatus, happenTime, crtAddr, eventImage, reason, zoneName, personId, personName, personFaceImage, deviceId, updTime));
			}
			FUYichangliebiaoPC data = FUYichangliebiaoPC(currPage, pageSize, rowCount, pageCount, eventList);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::getYichangbaojing(FString eventCode)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/list?eventCode=" + eventCode);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getYichangbaojingResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getYichangbaojingResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUYichangbaojing> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString eventCode = single->GetStringField("eventCode");
				FString eventName = single->GetStringField("eventName");
				FString eventType = single->GetStringField("eventType");
				FString eventStatus = single->GetStringField("eventStatus");
                FString longitude = single->GetStringField("longitude");
                FString latitude = single->GetStringField("latitude");
                FString deviceX = single->GetStringField("deviceX");
                FString deviceY = single->GetStringField("deviceY");
                FString deviceId = single->GetStringField("deviceId");
                FString deviceName = single->GetStringField("deviceName");
				FString happenTime = single->GetStringField("happenTime");
				FString crtAddr = single->GetStringField("crtAddr");
				FString eventImage = single->GetStringField("eventImage");
				data.Add(FUYichangbaojing(eventCode, eventName, eventType, eventStatus, longitude, latitude, deviceX, deviceY, deviceId, deviceName, happenTime, crtAddr, eventImage));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::getYichangDetail(FString eventCode)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/detail?eventCode=" + eventCode);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getYichangDetailResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getYichangDetailResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			FUYichangDetail data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString eventCode = single->GetStringField("eventCode");
				FString eventName = single->GetStringField("eventName");
				FString eventType = single->GetStringField("eventType");
				FString eventStatus = single->GetStringField("eventStatus");
                FString happenTime = single->GetStringField("happenTime");
                FString crtAddr = single->GetStringField("crtAddr");
                FString eventImage = single->GetStringField("eventImage");
                FString reason = single->GetStringField("reason");
                FString zoneName = single->GetStringField("zoneName");
                FString personId = single->GetStringField("personId");
                FString personName = single->GetStringField("personName");
                FString personFaceImage = single->GetStringField("personFaceImage");
                int32 isNeedSuppor = single->GetIntegerField("isNeedSuppor");
                FString deviceId = single->GetStringField("deviceId");
                FString deviceName = single->GetStringField("deviceName");
                FString handle_unit = single->GetStringField("handle_unit");
                FString finish_date = single->GetStringField("finish_date");
				FString deviceX = single->GetStringField("deviceX");
				FString deviceY = single->GetStringField("deviceY");
				data = FUYichangDetail(eventCode, eventName, eventType, eventStatus, happenTime, crtAddr, eventImage, reason, zoneName, personId, personName, personFaceImage, isNeedSuppor, deviceId, deviceName, handle_unit, finish_date, deviceX, deviceY);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::getYichangResultDetail(FString eventCode)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/resultDetail?eventCode=" + eventCode);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getYichangResultDetailResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getYichangResultDetailResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			FUYichangResultDetail data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString eventCode = single->GetStringField("eventCode");
				FString eventName = single->GetStringField("eventName");
				FString eventStatus = single->GetStringField("eventStatus");
                FString personId = single->GetStringField("personId");
                FString personName = single->GetStringField("personName");
                FString personFaceImage = single->GetStringField("personFaceImage");
                FString successTime = single->GetStringField("successTime");
                FString successDesc = single->GetStringField("successDesc");
				TArray<TSharedPtr<FJsonValue>> rawSuccessImage = single->GetArrayField("successImage");
				TArray<FString> successImage;
				for (int32 index2 = 0; index2 < rawSuccessImage.Num(); index2++)
				{
					successImage.Add(rawSuccessImage[index2]->AsString());
				}
				data = FUYichangResultDetail(eventCode, eventName, eventStatus, personId, personName, personFaceImage, successTime, successDesc, successImage);
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::resolveYichang(FString eventCode, FString type, TArray<FString> personIds)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
    FString ids = "";
    for (int32 index = 0; index < personIds.Num(); index++)
    {
        if(index != (personIds.Num() - 1)) {
            ids = ids + personIds[index] + ",";
        } else {
            ids = ids + personIds[index];
        }
    }
	HttpReuest->SetURL("http://localhost:31111/event/send?eventCode=" + eventCode + "&type=" + type + "&personIds=" + ids);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::resolveYichangResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::resolveYichangResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UYichangshijian::getYichanggaofadi(FString num)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/event/highHairList?showNum=" + num);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UYichangshijian::getYichanggaofadiResponse);
	HttpReuest->ProcessRequest();
}

void UYichangshijian::getYichanggaofadiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUYichanggaofadi> data; 
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				FString policeName = single->GetStringField("policeName"); 
				FString policeNum = single->GetStringField("policeNum"); 
				TArray<TSharedPtr<FJsonValue>> rawDevices = single->GetArrayField("devices");
				TArray<FUYichanggaofadiDevice> devices; 
				for (int32 index2 = 0; index2 < rawDevices.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawDevices[index2]->AsObject();
					FString deviceId = single2->GetStringField("deviceId"); 
					FString deviceName = single2->GetStringField("deviceName"); 
					FString deviceX = single2->GetStringField("deviceX"); 
					FString deviceY = single2->GetStringField("deviceY"); 
					FString zoneName = single2->GetStringField("zoneName"); 
					FString rtspUrl = single2->GetStringField("rtspUrl"); 
					FString longitude = single2->GetStringField("longitude"); 
					FString latitude = single2->GetStringField("latitude"); 
					devices.Add(FUYichanggaofadiDevice(deviceId, deviceName, deviceX, deviceY, zoneName, rtspUrl, longitude, latitude));
				}
				data.Add(FUYichanggaofadi(policeName, policeNum, devices));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}