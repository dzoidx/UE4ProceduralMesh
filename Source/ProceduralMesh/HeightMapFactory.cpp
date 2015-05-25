// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMesh.h"
#include "HeightMapFactory.h"


UHeightMapFactory::UHeightMapFactory(const FObjectInitializer & ObjectInitializer)
	: Super(ObjectInitializer)
{
	bCreateNew = false;
	bEditorImport = true;
	SupportedClass = UHeightMap::StaticClass();

	Formats.Add(TEXT("hm;Height Map"));
}

UObject * UHeightMapFactory::FactoryCreateBinary
	(
		UClass * InClass,
		UObject * InParent,
		FName InName,
		EObjectFlags Flags,
		UObject * Context,
		const TCHAR * Type,
		const uint8 *& Buffer,
		const uint8 * BufferEnd,
		FFeedbackContext * Warn
	)
{
	check(Type);
	
	auto intBuff = (unsigned int*)Buffer;
	auto w = *intBuff;
	auto h = *(++intBuff);
	auto dataBuff = reinterpret_cast<unsigned char*>(++intBuff);

	auto i = 0U;
	TArray<float> bakedData;
	while (BufferEnd - dataBuff >= 0)
	{
		bakedData.Add((float)*dataBuff / 255);
		++dataBuff;
	}

	auto result = ConstructObject<UHeightMap>(UHeightMap::StaticClass(), InParent, InName, Flags | RF_Transactional);
	result->Data = bakedData;
	result->Width = w;
	result->Height = h;

	return result;
}

