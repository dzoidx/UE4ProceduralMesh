#include "ProceduralMesh.h"
#include "ProceduralMeshTriangle.h"

void CreateMesh(UProceduralMeshComponent* mesh, const TArray<FProceduralMeshTriangle>& triangles)
{
	if (mesh == nullptr)
		return;

	TArray<FVector> verts;
	TArray<int32> tris;
	TArray<FVector> norms;
	TArray<FVector2D> uvs;
	TArray<FColor> colors;
	TArray<FProcMeshTangent> tangs;

	for (auto& tri : triangles)
	{
		auto norm = (tri.Vertex1.Position - tri.Vertex0.Position) * (tri.Vertex2.Position - tri.Vertex0.Position);
		tris.Add(verts.Num());
		verts.Add(tri.Vertex0.Position);
		norms.Add(norm);

		tris.Add(verts.Num());
		verts.Add(tri.Vertex1.Position);
		norms.Add(norm);

		tris.Add(verts.Num());
		verts.Add(tri.Vertex2.Position);
		norms.Add(norm);
	}

	mesh->CreateMeshSection(0, verts, tris, norms, uvs, colors, tangs, false);
}
