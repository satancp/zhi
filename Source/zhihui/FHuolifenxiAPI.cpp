// Fill out your copyright notice in the Description page of Project Settings.
#include "FHuolifenxiAPI.h"
#include "Http.h"
#include "Json.h"

void AFHuolifenxiAPI::getKeysTodayResponse(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	if (!HttpRequest.IsValid() || !HttpResponse.IsValid())
	{
		return;
	}
	else if (bSucceeded && EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		
	}
}

void AFHuolifenxiAPI::getKeysToday(char type)
{
	TSharedRef<IHttpRequest> HttpReuest = FHttpModule::Get().CreateRequest();
	HttpReuest->SetURL("http://localhost:31111/zhsa/keys/getList?showNum=10&channel=shuian&type=" + type);
	HttpReuest->SetVerb(TEXT("GET"));
	HttpReuest->SetHeader(TEXT("Content-Type"), TEXT("application/x-www-form-urlencoded"));
	HttpReuest->OnProcessRequestComplete().BindUObject(this, &AFHuolifenxiAPI::getKeysTodayResponse);
	HttpReuest->ProcessRequest();
}
