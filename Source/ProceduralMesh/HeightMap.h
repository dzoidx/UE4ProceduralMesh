// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "HeightMap.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALMESH_API UHeightMap : public UObject
{
	GENERATED_BODY()
	
public:
	UHeightMap(const FObjectInitializer& initializer);

	UPROPERTY(EditAnywhere, Category = "My Object Properties")
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Data")
	TArray<float> Data;

	UPROPERTY(EditAnywhere, Category = "Data")
	uint32 Width;

	UPROPERTY(EditAnywhere, Category = "Data")
	uint32 Height;

private:
	
};
