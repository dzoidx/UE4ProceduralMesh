// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "ProceduralMeshComponent.h"
#include "HeightMap.h"
#include "HeightMapActor.generated.h"

UCLASS()
class PROCEDURALMESH_API AHeightMapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHeightMapActor();

	// Height map raw data
	UPROPERTY(EditAnywhere, Category = HeightMap)
	UHeightMap* hm;

	// Generated mesh
	UPROPERTY(VisibleAnywhere, Category=Materials)
	UProceduralMeshComponent* mesh;

	// Height to vertex step
	UPROPERTY(EditAnywhere, Category = HeightMap)
	float Step;

	// Elevation scale
	UPROPERTY(EditAnywhere, Category = HeightMap)
	float HeightScale;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void OnConstruction(const FTransform& Transform);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	void RebuildMesh();
	
	
};
