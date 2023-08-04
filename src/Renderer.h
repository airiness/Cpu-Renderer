#pragma once
#include "Definition.h"
#include "VertexData.h"
#include "Camera.h"

struct BoundingBox
{
	Vec2i mMin = { 0,0 };
	Vec2i mMax = { Configuration::DisplayWidth, Configuration::DisplayHeight };
};

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer() = default;

	void ClearColorBuffer(Color color);
	void ClearDepthBuffer();

	ColorBuffer& GetColorBuffer() { return mColorBuffer; }
	DepthBuffer& GetDepthBuffer() { return mDepthBuffer; }

private:
	ColorBuffer mColorBuffer;
	DepthBuffer mDepthBuffer;
};

class Renderer
{
public:
	enum FillMode
	{
		Wireframe,
		Solid
	};

public:
	Renderer();
	~Renderer() = default;

	bool Initialize();
	void Destroy();
	void ClearBuffer();
	void SwapBuffer();

	FrameBuffer& GetFrameBuffer() { return mFrameBuffer; }
	ColorBuffer& GetColorBuffer() { return mFrameBuffer.GetColorBuffer(); }
	void SetModelMatrix(const Mat4f& m) { mModelMatrix = m; }
	void SetViewMatrix(const Mat4f& v) { mViewMatrix = v; }
	void SetProjectionMatrix(const Mat4f& p) { mProjectionMatrix = p; }

	void DrawTriangle(const TriangleColorVertex& t, FillMode fillmode = Solid);

public:
	static void DrawPoint2D(const Vec2f& pos, Color color, ColorBuffer* buffer);
	static void DrawLine2D(const Vec2f& begin, const Vec2f& end, Color color, ColorBuffer* buffer);
	static void DrawTriangle2D(const std::array<Vec2f, 3>& t, Color color, ColorBuffer* buffer);

private:
	static BoundingBox GetTriangleBoundingBox(const std::array<Vec2f, 3>& t);
	static Vec3f CalculateWeight(const std::array<Vec2f, 3>& vertices, const Vec2f& p);
	static float DepthInterpolate(const std::array<float, 3>& screenDepth, const Vec3f& weight);
	static Color ColorInterpolate(const std::array<Color, 3>& color, const Vec3f& weight);
	static bool IsBackFace(const std::array<Vec2f, 3>& screenCoord);

private:
	int32_t mWidth = Configuration::DisplayWidth;
	int32_t mHeight = Configuration::DisplayHeight;

	Color mClearColor = Color::Gray();

	FrameBuffer mFrameBuffer;

	Mat4f mModelMatrix;
	Mat4f mViewMatrix;
	Mat4f mProjectionMatrix;
};