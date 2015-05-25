// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Classes/Factories/Factory.h"
#include "HeightMap.h"
#include "HeightMapFactory.generated.h"

/**
 * 
 */
UCLASS()
class PROCEDURALMESH_API UHeightMapFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	
	UHeightMapFactory(const FObjectInitializer & ObjectInitializer);

	virtual UObject * FactoryCreateBinary(UClass * InClass, UObject * InParent, FName InName, EObjectFlags Flags, UObject * Context, const TCHAR * Type, const uint8 *& Buffer, const uint8 * BufferEnd, FFeedbackContext * Warn);
	
	
};
