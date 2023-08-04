#pragma once
#include "Definition.h"
#include "Color.h"

struct ColorVertex
{
	Vec3f mPosition;
	Color mColor;
	//Vec3f mNormal;
};

struct TexturedVertex
{
	Vec3f mPosition;
	Vec2f mTextureCoord;
	Vec3f mNormal;
};

using TriangleColorVertex = std::array<ColorVertex, 3>;
using TriangleTexturedVertex = std::array<TexturedVertex, 3>;