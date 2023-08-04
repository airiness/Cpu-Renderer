#pragma once
#include "Model.h"
#include "Camera.h"

class Scene
{
public:
	Scene();
	virtual ~Scene() = default;

	virtual void Initialize();
	virtual void Update();
	virtual void Render();

protected:
	std::vector<std::shared_ptr<Model>> mModels;

	Camera mCamera;
};

class PrimitiveScene : public Scene
{
public:
	PrimitiveScene();
	virtual ~PrimitiveScene() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;

	enum Primitives
	{
		Cube0,
		Triangle0,
		WireFrameCube0,
		Count
	};
};