#include "Terrain.h"
#include "TerrainModel.h"
#include "ShaderTextureLight.h"
#include "Texture.h"

Terrain::Terrain(ID3D11Device * dev, ShaderTextureLight * shader, Texture * texture, LPCWSTR heightmapFile, int RepeatU, int RepeatV, int width, int height)
{
	pTerrain = new TerrainModel(dev, heightmapFile, RepeatU, RepeatV, width, height);
	pTexLightShader = shader;
	pTexture = texture;
}

void Terrain::SendWorldAndMaterial(const Matrix& mat, const Vect& amb, const Vect& diff, const Vect& spec)
{
	myWorld = mat;
	ambient = amb;
	diffuse = diff;
	specular = spec;
}

void Terrain::Render()
{
	pTexLightShader->SendWorldAndMaterial(myWorld, ambient, diffuse, specular);
	pTexLightShader->SetTextureResourceAndSampler(pTexture);
	pTerrain->Render(pTexLightShader->GetContext());
}
