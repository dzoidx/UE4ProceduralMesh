// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralMesh.h"
#include "Terrain.h"


// Sets default values
ATerrain::ATerrain()
{
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralLathe"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> Material(TEXT("/Game/Materials/BaseColor.BaseColor"));
	mesh->SetMaterial(0, Material.Object);

	TArray<FProceduralMeshTriangle> triangles;
	GenerateTerrain(triangles);
	mesh->SetProceduralMeshTriangles(triangles);
}

// Called when the game starts or when spawned
void ATerrain::BeginPlay()
{
	Super::BeginPlay();
	TArray<FProceduralMeshTriangle> triangles;
	GenerateTerrain(triangles);
	mesh->SetProceduralMeshTriangles(triangles);
}

// Called every frame
void ATerrain::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}


void ATerrain::GenerateTerrain(TArray<FProceduralMeshTriangle>& OutTriangles)
{
	if (!HeightMap)
		return;
	auto mm = HeightMap->PlatformData->Mips[0];
	auto data = static_cast<FColor*>(mm.BulkData.Lock(LOCK_READ_ONLY));
	auto heightScale = 100.0;
	auto _step = -10.0;

	FProceduralMeshTriangle tri1;
	FProceduralMeshTriangle tri2;
	for (auto i = 0; i < mm.SizeX; i++)
	{
		for (auto j = 0; j < mm.SizeX; j++)
		{
			auto height = (float)data[i * mm.SizeX + j].R / 255.0 * heightScale;
			tri1.Vertex0.Position.Set(i * _step, j * _step, height);
			tri1.Vertex0.U = 0;
			tri1.Vertex0.V = 1;

			i++;
			height = (float)data[i * mm.SizeX + j].R / 255.0 * heightScale;
			tri1.Vertex1.Position.Set(i * _step, j * _step, height);
			tri1.Vertex1.U = 1;
			tri1.Vertex1.V = 1;
			i--;
			j++;

			height = (float)data[i * mm.SizeX + j].R / 255.0 * heightScale;
			tri1.Vertex2.Position.Set(i * _step, j * _step, height);
			tri1.Vertex2.U = 0;
			tri1.Vertex2.V = 0;
			tri2.Vertex0.Position = tri1.Vertex2.Position;
			tri2.Vertex0.U = 0;
			tri2.Vertex0.V = 0;
			j--;
			i++;

			height = (float)data[i * mm.SizeX + j].R / 255.0 * heightScale;
			tri2.Vertex1.Position.Set(i * _step, j * _step, height);
			tri2.Vertex1.U = 1;
			tri2.Vertex1.V = 1;
			j++;

			height = (float)data[i * mm.SizeX + j].R / 255.0 * heightScale;
			tri2.Vertex2.Position.Set(i * _step, j * _step, height);
			tri2.Vertex2.U = 1;
			tri2.Vertex2.V = 0;
			i--;
			j--;

			OutTriangles.Add(tri1);
			OutTriangles.Add(tri2);
		}
	}
	mm.BulkData.Unlock();
}
