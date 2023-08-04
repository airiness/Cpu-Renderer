#pragma once
#include "Definition.h"
#include "VertexData.h"
#include "Renderer.h"

class Model
{
public:
	Model();
	~Model() = default;

	void Update();
	void Draw(ColorBuffer* buffer);

	Mat4f GetModelMatrix();

	std::vector<ColorVertex>& GetVertices() { return mVertices; }
	const std::vector<ColorVertex>& GetVertices() const { return mVertices; }

	std::vector<int32_t>& GetIndices() { return mIndices; }
	const std::vector<int32_t>& GetIndices() const { return mIndices; }

	void SetPosition(const Vec3f& pos) { mPosition = pos; }
	void SetFillMode(Renderer::FillMode fillmode) { mFillMode = fillmode; };
public:
	static std::shared_ptr<Model> CreateTriangle();
	static std::shared_ptr<Model> CreateCube();

private:
	std::vector<ColorVertex> mVertices;
	std::vector<int32_t> mIndices;

	Renderer::FillMode mFillMode = Renderer::FillMode::Solid;

	Vec3f mPosition = Vec3f::Zero();
	Quaternion mRotation = Quaternion::Identity();
};