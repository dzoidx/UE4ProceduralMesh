#pragma once

#include "Engine.h"
#include "ProceduralMeshVertex.generated.h"

USTRUCT(BlueprintType)
struct FProceduralMeshVertex
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, Category = Triangle)
		FVector Position;

	UPROPERTY(EditAnywhere, Category = Triangle)
		FColor Color;

	UPROPERTY(EditAnywhere, Category = Triangle)
		float U;

	UPROPERTY(EditAnywhere, Category = Triangle)
		float V;
};
