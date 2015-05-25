// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMesh.h"
#include "HeightMapActor.h"


// Sets default values
AHeightMapActor::AHeightMapActor()
	: Step(5.0f), HeightScale(15.0f)
{
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("HeightMapMesh"));
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (hm != nullptr)
		RebuildMesh();
}

// Called when the game starts or when spawned
void AHeightMapActor::BeginPlay()
{
	if (hm != nullptr)
		RebuildMesh();
	Super::BeginPlay();
	
}

// Called every frame
void AHeightMapActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

#if WITH_EDITOR

void AHeightMapActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	auto PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AHeightMapActor, hm) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AHeightMapActor, HeightScale) ||
		PropertyName == GET_MEMBER_NAME_CHECKED(AHeightMapActor, Step))
	{
		RebuildMesh();
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

void AHeightMapActor::OnConstruction(const FTransform& Transform)
{
	if (hm == nullptr)
		return;

	RebuildMesh();
}

void AHeightMapActor::RebuildMesh()
{
	FProceduralMeshTriangle t1;
	FProceduralMeshTriangle t2;
	TArray<FProceduralMeshTriangle> OutTriangles;

	for (auto i = 0U; i < hm->Width - 1; ++i)
	{
		for (auto j = 0U; j < hm->Height - 1; ++j)
		{
			auto h0 = hm->Data[i * hm->Width + j];
			auto h1 = hm->Data[hm->Width * i + j + 1];
			auto h2 = hm->Data[hm->Width * (i + 1) + j];
			auto h3 = hm->Data[hm->Width * (i + 1) + j + 1];
			FVector p0 = FVector(-(float)i * Step, -(float)j * Step, HeightScale * h0);
			FVector p1 = FVector(-(float)i * Step, -((float)j + 1) * Step, HeightScale * h1);
			FVector p2 = FVector(-((float)i + 1) * Step, -(float)j * Step, HeightScale * h2);
			FVector p3 = FVector(-((float)i + 1) * Step, -((float)j + 1) * Step, HeightScale * h3);
			FProceduralMeshVertex v0;
			FProceduralMeshVertex v1;
			FProceduralMeshVertex v2;
			FProceduralMeshVertex v3;

			v0.Position = p0;
			v1.Position = p1;
			v2.Position = p2;
			v3.Position = p3;

			t1.Vertex0 = v0;
			t1.Vertex1 = v1;
			t1.Vertex2 = v2;

			t2.Vertex0 = v2;
			t2.Vertex1 = v1;
			t2.Vertex2 = v3;

			OutTriangles.Add(t1);
			OutTriangles.Add(t2);
		}
	}
	mesh->SetProceduralMeshTriangles(OutTriangles);
}
