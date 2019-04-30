// ShaderTextureLight
// Andre Berthiaume, Feb 2017

#ifndef _ShaderTextureLight3Point
#define _ShaderTextureLight3Point

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class ShaderTextureLight3Point : public ShaderBase
{

public:
	ShaderTextureLight3Point(const ShaderTextureLight3Point&) = delete;				 // Copy constructor
	ShaderTextureLight3Point(ShaderTextureLight3Point&&) = default;                    // Move constructor
	ShaderTextureLight3Point& operator=(const ShaderTextureLight3Point&) & = default;  // Copy assignment operator
	ShaderTextureLight3Point& operator=(ShaderTextureLight3Point&&) & = default;       // Move assignment operator
	~ShaderTextureLight3Point();		  							         // Destructor

	ShaderTextureLight3Point(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLight1Parameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLight2Parameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLight3Parameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SetTextureResourceAndSampler(Texture* tex);
	void SendFogParameters(float mFogStart, float mFogRange, const Vect& mFogColor);

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;
	PointLight PointLightData;
	PointLight PointLightData2;
	PointLight PointLightData3;

	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		PointLight PntLight2;
		PointLight PntLight3;
		Vect EyePosWorld;
	};

	ID3D11Buffer*  mpBufferLightParams;

	struct Data_FogParams
	{
		float fogStart;
		float fogRange;
		Vect fogColor;
	};

	Data_FogParams df;

	float defaultStart = 1.0f;
	float defaultRange = 6500.0f;
	Vect defaultColor = Vect(1, 1, 1);

	ID3D11Buffer*  mpBufferFogParams;

};

#endif _ShaderTextureLight3Point

