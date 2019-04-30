// DXApp
// Andre Berthiaume, June 2016
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "Skybox.h"
#include "ShaderColor.h"
#include "ShaderTexture.h"
#include "ShaderColorLight.h"
#include "ShaderTextureLight.h"
#include "ShaderTextureLight3Point.h"
#include "ShaderTextureLightMultipleSpot.h"
#include "GraphicObject_Color.h"
#include "GraphicObject_ColorLight.h"
#include "GraphicObject_Texture.h"
#include "GraphicObject_TextureLight.h"
#include "GraphicObject_TexLight3Point.h"
#include "Terrain.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;
	Matrix mWorld;	
	Matrix mWorld2;
	Matrix mWorldTent;
	Matrix mWorldTent2;
	Matrix mWorldMonster;
	Matrix mWorldMonster2;
	Matrix mWorldCar;
	Matrix mWorldTree;
	Matrix mWorldCabin;
	Matrix mWorldLight1;
	Matrix mWorldLight2;

	Matrix mWorldLight;
	Vect pointLight1;
	Vect pointLight2;

	Skybox* pSkybox;

	Model* pModelMonster;
	Model* pSphere;
	Model* pModelTent;
	Model* pModelCar;
	Model* pModelTree;
	Model* pModelCabin;

	Texture* mTexTent;
	Texture* mTexMonster;
	Texture* mTexPlane;
	Texture* mTexSky;
	Texture* mTexCar;
	Texture* mTexWheel;
	Texture* mTexTree;
	Texture* mTexCottage1;

	GraphicObject_TextureLight* colorLightTent;
	GraphicObject_TextureLight* colorLightTent2;
	GraphicObject_TextureLight* texLightMonster;
	GraphicObject_TextureLight* texLightMonster2;
	GraphicObject_TextureLight* texLightTree;
	GraphicObject_TextureLight* texLightCabin;
	GraphicObject_TexLight3Point* Point3LightCar;

	FlatPlane* pWater;
	Terrain* pTerrain;
	Matrix mPlaneMat;
	Matrix mBackPlane;

	ShaderTexture* pTextureShader;
	ShaderColor* pShaderColor;
	ShaderColorLight* pShaderColLight;
	ShaderTextureLight* pShaderTexLight;
	ShaderTextureLight3Point* pShaderTexLight3Point;

	// Bringing these back temporarily


	// gimmicky mouse control
	Vect MousePos;		
	float mTheta;
	float mPhi;
	float mRadius;
	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp