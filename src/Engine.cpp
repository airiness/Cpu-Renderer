#include "Engine.h"

#include <iostream>
#include <SDL_video.h>

Engine& Engine::Instance()
{
	static Engine instance;
	return instance;
}

bool Engine::Initialize()
{
	auto result = mDisplay.Initialize();
	if (result == false) { return false; }

	result = mRenderer.Initialize();
	if (result == false) { return false; }

	mCurrentScene = std::make_unique<PrimitiveScene>();

	mCurrentScene->Initialize();
	return true;
}

void Engine::Update()
{
	int frameCount = 0;
	bool done = false;

	while (!done)
	{
		done = HandleInput();

		mCurrentScene->Update();

		mRenderer.ClearBuffer();
		mCurrentScene->Render();
		mRenderer.SwapBuffer();

		frameCount++;
	}
}

void Engine::Destroy()
{
	mRenderer.Destroy();
	mDisplay.Destroy();
}

bool Engine::HandleInput()
{
	bool isDone = false;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isDone = true;
			break;
		}
		else
		{
			isDone = HandleInputEvent(&event);
		}
	}

	return isDone;
}

bool Engine::HandleInputEvent(SDL_Event* event)
{
	bool isEscape = false;

	if (event->type == SDL_KEYDOWN)
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isEscape = true;
		default:
			break;
		}
	}
	return isEscape;
}