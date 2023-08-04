#pragma once
#include "Definition.h"

#include <memory>
#include <functional>
#include <SDL.h>

class Display
{
public:
	bool Initialize();
	void Destroy();

	void SwapBuffer(ColorBuffer* buffer);

private:
	SDL_Window* mWindow = nullptr;
	SDL_Surface* mSurface = nullptr;
};

