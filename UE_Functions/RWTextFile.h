// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RWTextFile.generated.h"

UCLASS(Blueprintable, BlueprintType)
class CREATESIMUV6_API URWTextFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Save", meta = (Keywords = "LoadTxt"))
		static bool LoadTxt(FString FilePath, FString FileName, FString& SaveText);

	UFUNCTION(BlueprintPure, Category = "Save", meta = (Keywords = "LoadTxt"))
		static bool LoadArrayTxt(FString FilePath, FString FileName, TArray<FString>& SaveText);

	UFUNCTION(BlueprintCallable, Category = "Save", meta = (Keywords = "SaveTxt"))
		static bool SaveTxt(FString FilePath, FString SaveText, FString FileName);

	UFUNCTION(BlueprintCallable, Category = "Save", meta = (Keywords = "SaveArrayTxt"))
		static bool SaveArrayTxt(FString FilePath, TArray<FString> SaveText, FString FileName);

	UFUNCTION(BlueprintCallable, Category = "Save", meta = (Keywords = "SaveArrayTxt"))
		static bool SaveArrayTxtAppend(FString FilePath, TArray<FString> SaveText, FString FileName);

};
