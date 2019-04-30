#ifndef _Terrain
#define _Terrain

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class TerrainModel;
class ShaderTextureLight;
class Texture;
struct ID3D11DeviceContext;
struct ID3D11Device;

class Terrain
{

private:
	TerrainModel* pTerrain;
	Texture* pTexture;
	ShaderTextureLight* pTexLightShader;
	Matrix myWorld;
	Vect ambient;
	Vect diffuse;
	Vect specular;

public:
	Terrain(ID3D11Device* dev, ShaderTextureLight* shader, Texture* texture, LPCWSTR heightmapFile, int RepeatU, int RepeatV, int width, int height);

	void SendWorldAndMaterial(const Matrix& mat, const Vect& amb = Vect(1, 1, 1), const Vect& diff = Vect(1, 1, 1), const Vect& spec = Vect(1, 1, 1));

	void Render();

};



#endif _Skybox