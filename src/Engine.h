#pragma once
#include "Display.h"
#include "Renderer.h"
#include "Scene.h"
#include <SDL.h>

class Engine
{
public:
	static Engine& Instance();
public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	bool Initialize();
	void Update();
	void Destroy();

	Display& GetDisplay() { return mDisplay; }
	Renderer& GetRenderer() { return mRenderer; }

private:
	Engine() = default;
	~Engine() = default;

	bool HandleInput();
	bool HandleInputEvent(SDL_Event* event);

private:
	Display mDisplay;
	Renderer mRenderer;

	std::unique_ptr<Scene> mCurrentScene;
};