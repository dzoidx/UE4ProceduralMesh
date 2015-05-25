// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Terrain.generated.h"

UCLASS()
class PROCEDURALMESH_API ATerrain : public AActor
{
	GENERATED_BODY()

	

public:	
	// Sets default values for this actor's properties
	ATerrain();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void GenerateTerrain(TArray<FProceduralMeshTriangle>& OutTriangles);

	UPROPERTY(EditAnywhere, Category = HeightMap)
		UTexture2D* HeightMap;

	UPROPERTY(VisibleAnywhere, Category = Materials)
		UProceduralMeshComponent* mesh;
	
};
