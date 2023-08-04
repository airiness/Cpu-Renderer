#include "Scene.h"
#include "Engine.h"

Scene::Scene()
{
}

void Scene::Initialize()
{
}

void Scene::Update()
{
	for (auto& m : mModels)
	{
		m->Update();
	}
}

void Scene::Render()
{
	auto& renderer = Engine::Instance().GetRenderer();

	renderer.SetViewMatrix(mCamera.GetViewMatrix());
	renderer.SetProjectionMatrix(mCamera.GetPerspProjMatrix());

	for (auto& m : mModels)
	{
		renderer.SetModelMatrix(m->GetModelMatrix());

		m->Draw(&renderer.GetColorBuffer());
	}
}

PrimitiveScene::PrimitiveScene()
{
}

void PrimitiveScene::Initialize()
{
	Scene::Initialize();
	
	mModels.reserve(Primitives::Count);
	mModels.emplace_back(Model::CreateCube());
	mModels.emplace_back(Model::CreateTriangle());
	mModels.emplace_back(Model::CreateCube());

	mModels.at(Cube0)->SetPosition(Vec3f(3.0f, 0.0f, 0.0f));
	mModels.at(Triangle0)->SetPosition(Vec3f(-3.0f, 0.0f, 0.0f));

	auto& wireframeCube = mModels.at(WireFrameCube0);
	wireframeCube->SetPosition(Vec3f(0.0f, 0.0f, -3.0f));
	wireframeCube->SetFillMode(Renderer::FillMode::Wireframe);
}

void PrimitiveScene::Update()
{
	Scene::Update();
}

void PrimitiveScene::Render()
{
	Scene::Render();
}