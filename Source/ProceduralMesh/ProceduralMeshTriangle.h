#pragma once

#include "ProceduralMeshVertex.h"
#include "ProceduralMeshComponent.h"
#include "ProceduralMeshTriangle.generated.h"

USTRUCT(BlueprintType)
struct FProceduralMeshTriangle
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = Triangle)
		FProceduralMeshVertex Vertex0;

	UPROPERTY(EditAnywhere, Category = Triangle)
		FProceduralMeshVertex Vertex1;

	UPROPERTY(EditAnywhere, Category = Triangle)
		FProceduralMeshVertex Vertex2;
};

void CreateMesh(UProceduralMeshComponent* mesh, const TArray<FProceduralMeshTriangle>& triangles);




