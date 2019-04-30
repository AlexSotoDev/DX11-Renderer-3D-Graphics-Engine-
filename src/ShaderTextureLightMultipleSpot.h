//ShaderTextureLightMultipleSpot

#ifndef _ShaderTextureLightMultipleSpot
#define _ShaderTextureLightMultipleSpot

#include "ShaderBase.h"
#include "Matrix.h"

struct ID3D11Buffer;
struct ID3D11Device;

class Texture;

class ShaderTextureLightMultipleSpot : public ShaderBase
{

public:
	ShaderTextureLightMultipleSpot(const ShaderTextureLightMultipleSpot&) = delete;				 // Copy constructor
	ShaderTextureLightMultipleSpot(ShaderTextureLightMultipleSpot&&) = default;                    // Move constructor
	ShaderTextureLightMultipleSpot& operator=(const ShaderTextureLightMultipleSpot&) & = default;  // Copy assignment operator
	ShaderTextureLightMultipleSpot& operator=(ShaderTextureLightMultipleSpot&&) & = default;       // Move assignment operator
	~ShaderTextureLightMultipleSpot();		  							         // Destructor

	ShaderTextureLightMultipleSpot(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetSpotLight1Parameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLight2Parameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLight3Parameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));
	void SendFogParameters(float mFogStart, float mFogRange, const Vect& mFogColor);

	void SetTextureResourceAndSampler(Texture* tex);

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

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData;
	SpotLight SpotLightData2;
	SpotLight SpotLightData3;

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
		SpotLight SptLight;
		SpotLight SptLight2;
		SpotLight SptLight3;
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

#endif _ShaderTextureLightMultipleSpot
