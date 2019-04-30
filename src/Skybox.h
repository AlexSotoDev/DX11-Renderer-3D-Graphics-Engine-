#ifndef _Skybox
#define _Skybox

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
class ShaderTexture;
class Texture;
struct ID3D11DeviceContext;
struct ID3D11Device;

class Skybox
{

private:
	Model* pSkybox;
	Texture* pTexture;
	ShaderTexture* pTexShader;
	Matrix myWorld;

public:
	Skybox(ID3D11Device* dev, ShaderTexture* shader, Texture* tex, float size);

	void SendWorld(const Matrix& mat);

	void Render();

};



#endif _Skybox