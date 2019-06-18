// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineUtils.h"
#include "Engine/DataTable.h"

#include "CoreMinimal.h"
#include "CoreUObject.h"

#include <vector>
#include <string>

#include "GameFramework/Actor.h"
#include "GeneretedObjectV2.generated.h"

USTRUCT(BlueprintType, meta = (IsBlueprintBase = true, BlueprintSpawnableComponent))
struct FColliderStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BlueprintSpawnableComponent, BlueprintAssignable = true))
		int Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BlueprintSpawnableComponent, BlueprintAssignable = true))
		TArray<FVector> Vertices;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BlueprintSpawnableComponent, BlueprintAssignable = true))
		TArray<int> Triangles;

	FColliderStruct()
	{
		Index = 0;
		Vertices.Empty();
		Triangles.Empty();
	}
};

UCLASS()
class CREATESIMUV6_API AGeneretedObjectV2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneretedObjectV2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, meta = (Keywords = "ParseTxt"))
		TArray<FColliderStruct> ParseTxt(FString FilePath, FString FileName);
	UFUNCTION(BlueprintCallable, meta = (Keywords = "NbCollider"))
		int RecupNbCollider(FString FilePath, FString FileName);
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Dimension"))
		float LectureMeshDimension(FString FilePath, FString FileName);
	UFUNCTION(BlueprintCallable, meta = (Keywords = "Normal"))
		FVector GenTriNormal(FVector Vert1, FVector Vert2, FVector Vert3);

public:
	void split(const std::string &in, std::vector<std::string> &out, std::string token);
	std::string tail(const std::string &in);
	std::string firstToken(const std::string &in);
};
