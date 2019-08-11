// Fill out your copyright notice in the Description page of Project Settings.


#include "QitaAPI.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

UQitaAPI::UQitaAPI() {

}

void UQitaAPI::getXiaoxi(int32 currPage, int32 pageSize, FString seachValue = "", int32 status = -1)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("currPage"), currPage);
	JsonObject->SetNumberField(TEXT("pageSize"), pageSize);
	if (seachValue != "") {
		JsonObject->SetStringField(TEXT("seachValue"), seachValue);
	}
	if (status != -1) {
		JsonObject->SetNumberField(TEXT("status"), status);
	}
	FString OutputString;
	TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/message/getList");
	HttpReuest->SetVerb(TEXT("POST"));
	HttpReuest->SetHeader("Content-Type", "application/json");
	HttpReuest->SetContentAsString(OutputString);
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UQitaAPI::getXiaoxiResponse);
	HttpReuest->ProcessRequest();
}

void UQitaAPI::getXiaoxiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			TArray<FUXiaoxi> data;
			TArray<TSharedPtr<FJsonValue>> rawData = JsonObject->GetArrayField("data");
			for (int32 index = 0; index < rawData.Num(); index++)
			{
				TSharedPtr<FJsonObject> single = rawData[index]->AsObject();
				TArray<TSharedPtr<FJsonValue>> rawMessageList = single->GetArrayField("messageList");
				int32 currPage = single->GetIntegerField("currPage");
				int32 pageSize = single->GetIntegerField("pageSize");
				int32 rowCount = single->GetIntegerField("rowCount");
				int32 pageCount = single->GetIntegerField("pageCount");
				TArray<FUXiaoxiSingle> messageList;
				for (int32 index2 = 0; index2 < rawMessageList.Num(); index2++)
				{
					TSharedPtr<FJsonObject> single2 = rawMessageList[index2]->AsObject();
					int32 msgId = single2->GetIntegerField("msgId");
					FString userName = single2->GetStringField("userName");
					FString content = single2->GetStringField("content");
					FString crtTime = single2->GetStringField("crtTime");
					TArray<TSharedPtr<FJsonValue>> rawImagesUrl = single2->GetArrayField("imagesUrl");
					TArray<FString> imagesUrl;
					for (int32 index3 = 0; index3 < rawImagesUrl.Num(); index3++)
					{
						imagesUrl.Add(rawImagesUrl[index3]->AsString());
					}
					messageList.Add(FUXiaoxiSingle(msgId, userName, content, crtTime, imagesUrl));
				}
				data.Add(FUXiaoxi(currPage, pageSize, rowCount, pageCount, messageList));
			}
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}

void UQitaAPI::getTianqi()
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/weather/index");
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &UQitaAPI::getTianqiResponse);
	HttpReuest->ProcessRequest();
}

void UQitaAPI::getTianqiResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
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
			FString temperature = single->GetStringField("temperature");
			FString weather = single->GetStringField("weather");
			FString weather_id_fa = single->GetStringField("weather_id_fa");
			FString weather_id_fb = single->GetStringField("weather_id_fb");
			FString wind = single->GetStringField("wind");
			FString week = single->GetStringField("week");
			FString city = single->GetStringField("city");
			FString date_y = single->GetStringField("date_y");
			FString dressing_index = single->GetStringField("dressing_index");
			FString dressing_advice = single->GetStringField("dressing_advice");
			FString uv_index = single->GetStringField("uv_index");
			FString comfort_index = single->GetStringField("comfort_index");
			FString wash_index = single->GetStringField("wash_index");
			FString travel_index = single->GetStringField("travel_index");
			FString exercise_index = single->GetStringField("exercise_index");
			FString aqi = single->GetStringField("aqi");
			FString quality = single->GetStringField("quality");
			FUTianqi data = FUTianqi(temperature, weather, weather_id_fa, weather_id_fb, wind, week, city, date_y, dressing_index, dressing_advice, uv_index, comfort_index, wash_index, travel_index, exercise_index, aqi, quality);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(code));
		}
	}
}