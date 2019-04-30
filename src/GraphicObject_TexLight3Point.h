// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_TexLight3Point
#define _GraphicObject_TexLight3Point

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTextureLight3Point.h"

class Texture;

class GraphicObject_TexLight3Point : public GraphicObject_Base
{
	friend class ShaderTextureLight3Point;

public:
	GraphicObject_TexLight3Point(const GraphicObject_TexLight3Point&) = delete;				 // Copy constructor
	GraphicObject_TexLight3Point(GraphicObject_TexLight3Point&&) = default;                    // Move constructor
	GraphicObject_TexLight3Point& operator=(const GraphicObject_TexLight3Point&) & = default;  // Copy assignment operator
	GraphicObject_TexLight3Point& operator=(GraphicObject_TexLight3Point&&) & = default;       // Move assignment operator
	~GraphicObject_TexLight3Point();		  											 // Destructor

	GraphicObject_TexLight3Point() = delete;

	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshnum);
	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec);
	void SetMaterial(const Vect& amb, const Vect& diff, const Vect& spec, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render() override;

	GraphicObject_TexLight3Point(ShaderTextureLight3Point* shader, Model* mod);

private:
	ShaderTextureLight3Point*					pShader;

	//Vect							Color;
	Texture**						MeshTextures;
	Vect*							MeshMaterials;

	Matrix							World;

};

#endif _GraphicObject_TexLight3Point
