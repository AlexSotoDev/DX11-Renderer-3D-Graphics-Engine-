#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, int RepeatU, int RepeatV, int width, int height)
{
	int nverts = width * width;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = ((width - 1) * (width - 1)) * 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	size_t side = hgtmap->height;	// the image should be square
	size_t pixel_width = 4;			// 4 bytes RGBA per pixel
	uint8_t h_val = hgtmap->pixels[pixel_width * (5 * side + 3)]; // the 'R' byte of the pixel at (3,5)

	int rowCells = width - 1;
	int rowCols = width - 1;

	float xOffset = -rowCols * 0.5f;
	float zOffset = rowCells * 0.5f;

	int cellSizeX = 1;
	int cellSizeZ = 1;

	float du = 1.0f / (width - 1);
	float dv = 1.0f / (width - 1);

	int k = 0;
	for (float i = 0; i < width; ++i) {

		for (float j = 0; j < width; ++j)
		{
			size_t myI = (size_t)i;
			size_t myJ = (size_t)j;

			h_val = hgtmap->pixels[pixel_width * (myJ * side + myI)];

			float yVal = (float)h_val;
			// Offset y-value by R value in RGB pixel
			pVerts[k].set(j * cellSizeX + xOffset, (yVal / 255.0f) * height, -i * cellSizeZ + zOffset, i * du * RepeatU, j * dv * RepeatV);

			++k;
		}
	}

	k = 0;
	for (DWORD i = 0; i < (DWORD)rowCells; ++i)
	{
		for (DWORD j = 0; j < (DWORD)rowCols; ++j)
		{
			pTriList[k].set(i * width + j, i * width + j + 1, (i + 1) * width + j);
			pTriList[k + 1].set((i + 1) * width + j, i * width + j + 1, (i + 1) * width + j + 1);
			k += 2;
		}
	}

	for (int i = 0; i < ntri; i++)
	{
		int index1 = pTriList[i].v0;
		int index2 = pTriList[i].v1;
		int index3 = pTriList[i].v2;

		Vect side1 = pVerts[index1].Pos - pVerts[index3].Pos;
		Vect side2 = pVerts[index1].Pos - pVerts[index2].Pos;
		Vect mynormal = side2.cross(side1);

		pVerts[index1].normal = Vect(0, 0, 0);
		pVerts[index2].normal = Vect(0, 0, 0);
		pVerts[index3].normal = Vect(0, 0, 0);

		pVerts[index1].normal += mynormal;
		pVerts[index2].normal += mynormal;
		pVerts[index3].normal += mynormal;
	}

	pTerrain = new Model(dev, pVerts, nverts, pTriList, ntri);

}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pTerrain->Render(context);
}