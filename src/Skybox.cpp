#include "Skybox.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include "ShaderTexture.h"
#include "Texture.h"
#include <assert.h>


Skybox::Skybox(ID3D11Device* dev, ShaderTexture* shader, Texture* tex, float size)
{
	pSkybox = new Model(dev, Model::PreMadedeModels::UnitSkyBoxSixFaceTexture, size);
	pTexture = tex;
	pTexShader = shader;
}

void Skybox::SendWorld(const Matrix & mat)
{
	myWorld = mat;
}

void Skybox::Render()
{
	pTexShader->SendWorld(myWorld);
	pTexShader->SetTextureResourceAndSampler(pTexture);
	pSkybox->Render(pTexShader->GetContext());
}