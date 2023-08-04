#include "Model.h"
#include "Renderer.h"
#include "Engine.h"

Model::Model()
{
}

void Model::Update()
{
	static float theta = 0.0f;
	theta += Math::ToRadian(0.03f);

	mRotation.w() = std::cos(theta);
	mRotation.y() = std::sin(theta);
}

void Model::Draw(ColorBuffer* buffer)
{
	auto& renderer = Engine::Instance().GetRenderer();

	const auto faceCount = mIndices.size() / 3;
	for (size_t i = 0; i < faceCount; i++)
	{
		std::array<ColorVertex, 3> vertices =
		{
			mVertices.at(mIndices.at(3 * i)),
			mVertices.at(mIndices.at(3 * i + 1)),
			mVertices.at(mIndices.at(3 * i + 2))
		};
		renderer.DrawTriangle(vertices, mFillMode);
	}
}

Mat4f Model::GetModelMatrix()
{
	Mat4f rotationMat = Mat4f::Identity();
	rotationMat.block(0, 0, 3, 3) = mRotation.toRotationMatrix();
	Mat4f translateMat = Mat4f::Identity();
	translateMat <<
		1.0f, 0.0f, 0.0f, mPosition.x(),
		0.0f, 1.0f, 0.0f, mPosition.y(),
		0.0f, 0.0f, 1.0f, mPosition.z(),
		0.0f, 0.0f, 0.0f, 1.0f;
	return translateMat * rotationMat;
}

std::shared_ptr<Model> Model::CreateTriangle()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();

	std::vector<int32_t> indices =
	{
		0, 1, 2,
	};

	std::vector<ColorVertex> vertices =
	{
		ColorVertex{Vec3f(-1.0f, -1.0f, 0.0f), Color::Blue()},
		ColorVertex{Vec3f(1.0f, -1.0f, 0.0f), Color::Yellow()},
		ColorVertex{Vec3f(1.0f, 1.0f, 0.0f), Color::Red()},
	};

	model->GetIndices() = indices;
	model->GetVertices() = vertices;

	return model;
}

std::shared_ptr<Model> Model::CreateCube()
{
	std::shared_ptr<Model> model = std::make_shared<Model>();

	std::vector<int32_t> indices =
	{
		1, 0, 3,
		3, 2, 1,
		4, 5, 6,
		6, 7, 4,
		8, 11, 10,
		10, 9, 8,
		12, 13, 14,
		14, 15, 12,
		17, 16, 19,
		19, 18, 17,
		20, 21, 22,
		22, 23, 20,
	};

	std::vector<ColorVertex> vertices =
	{
		ColorVertex{Vec3f(-1.0f, -1.0f, -1.0f), Color::Blue()},
		ColorVertex{Vec3f(1.0f, -1.0f, -1.0f), Color::Yellow()},
		ColorVertex{Vec3f(1.0f, 1.0f, -1.0f), Color::Red()},
		ColorVertex{Vec3f(-1.0f, 1.0f, -1.0f), Color::Green()},

		ColorVertex{Vec3f(-1.0f, -1.0f, 1.0f), Color::Pink()},
		ColorVertex{Vec3f(1.0f, -1.0f, 1.0f), Color::Cyan()},
		ColorVertex{Vec3f(1.0f, 1.0f, 1.0f), Color::DeepSkyBlue()},
		ColorVertex{Vec3f(-1.0f, 1.0f, 1.0f), Color::Orange()},

		ColorVertex{Vec3f(-1.0f, 1.0f, -1.0f), Color::Green()},
		ColorVertex{Vec3f(1.0f, 1.0f, -1.0f), Color::Red()},
		ColorVertex{Vec3f(1.0f, 1.0f, 1.0f), Color::DeepSkyBlue()},
		ColorVertex{Vec3f(-1.0f, 1.0f, 1.0f), Color::Orange()},

		ColorVertex{Vec3f(-1.0f, -1.0f, -1.0f), Color::Blue()},
		ColorVertex{Vec3f(1.0f, -1.0f, -1.0f), Color::Yellow()},
		ColorVertex{Vec3f(1.0f, -1.0f, 1.0f), Color::Cyan()},
		ColorVertex{Vec3f(-1.0f, -1.0f, 1.0f), Color::Pink()},

		ColorVertex{Vec3f(-1.0f, -1.0f, 1.0f), Color::Pink()},
		ColorVertex{Vec3f(-1.0f, -1.0f, -1.0f), Color::Blue()},
		ColorVertex{Vec3f(-1.0f, 1.0f, -1.0f), Color::Green()},
		ColorVertex{Vec3f(-1.0f, 1.0f, 1.0f), Color::Orange()},

		ColorVertex{Vec3f(1.0f, -1.0f, 1.0f), Color::Cyan()},
		ColorVertex{Vec3f(1.0f, -1.0f, -1.0f), Color::Yellow()},
		ColorVertex{Vec3f(1.0f, 1.0f, -1.0f), Color::Red()},
		ColorVertex{Vec3f(1.0f, 1.0f, 1.0f), Color::DeepSkyBlue()},
	};

	model->GetIndices() = indices;
	model->GetVertices() = vertices;

	return model;
}
