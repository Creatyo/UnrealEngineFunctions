// Fill out your copyright notice in the Description page of Project Settings.

#include "RWTextFile.h"
#include "FileHelper.h"

bool URWTextFile::LoadTxt(FString FilePath, FString FileName, FString& SaveText)
{
	return FFileHelper::LoadFileToString(SaveText, *(FilePath + FileName));
}

bool URWTextFile::LoadArrayTxt(FString FilePath, FString FileName, TArray<FString>& SaveText)
{
	return FFileHelper::LoadFileToStringArray(SaveText, *(FilePath + FileName));
}

bool URWTextFile::SaveTxt(FString FilePath, FString SaveText, FString FileName)
{
	return FFileHelper::SaveStringToFile(SaveText, *(FilePath + FileName), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}

bool URWTextFile::SaveArrayTxt(FString FilePath, TArray<FString> SaveText, FString FileName)
{
	return FFileHelper::SaveStringArrayToFile(SaveText, *(FilePath + FileName), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
}

bool URWTextFile::SaveArrayTxtAppend(FString FilePath, TArray<FString> SaveText, FString FileName)
{
	return FFileHelper::SaveStringArrayToFile(SaveText, *(FilePath + FileName), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}