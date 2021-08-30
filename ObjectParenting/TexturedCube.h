#pragma once
#include "Quad.h"
#include "Vector2D.h"
class TexturedCube :
    public Quad
{
public:
	TexturedCube(string name);
	~TexturedCube();

	void draw(int width, int height) override;
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};
};

