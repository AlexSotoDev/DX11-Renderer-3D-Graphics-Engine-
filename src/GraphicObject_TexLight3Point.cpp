#include "GraphicObject_TexLight3Point.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>
#include "Texture.h"

GraphicObject_TexLight3Point::GraphicObject_TexLight3Point(ShaderTextureLight3Point* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	MeshTextures = new Texture*[n];
	for (int i = 0; i < n; i++)
	{
		MeshTextures[i] = nullptr;
	}

	n = mod->GetMeshCount() * 3;
	MeshMaterials = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		MeshMaterials[i] = Vect(0, 0, 0);
	}
}

GraphicObject_TexLight3Point::~GraphicObject_TexLight3Point()
{
	delete[] MeshTextures;
}

void GraphicObject_TexLight3Point::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshTextures[i] = tex;
}

void GraphicObject_TexLight3Point::SetTexture(Texture* tex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshTextures[meshnum] = tex;
}

void GraphicObject_TexLight3Point::SetMaterial(const Vect & amb, const Vect & diff, const Vect & spec)
{
	for (int i = 0; i < this->pModel->GetMeshCount() * 3; i += 3)
	{
		MeshMaterials[i] = amb;
		MeshMaterials[i + 1] = diff;
		MeshMaterials[i + 2] = spec;
	}
}

void GraphicObject_TexLight3Point::SetMaterial(const Vect & amb, const Vect & diff, const Vect & spec, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshMaterials[meshnum * 3] = amb;
	MeshMaterials[meshnum * 3 + 1] = diff;
	MeshMaterials[meshnum * 3 + 2] = spec;
}

void GraphicObject_TexLight3Point::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TexLight3Point::Render()
{
	pModel->BindVertexIndexBuffers(pShader->GetContext());
	int count = 0;
	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldAndMaterial(World, MeshMaterials[count], MeshMaterials[count + 1], MeshMaterials[count + 2]);
		pShader->SetTextureResourceAndSampler(MeshTextures[i]);
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}