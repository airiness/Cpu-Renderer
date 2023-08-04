#include "Display.h"
#include "Renderer.h"

bool Display::Initialize()
{
	auto result = SDL_Init(SDL_INIT_VIDEO) == 0;
	if (!result)
	{
		ConsoleLog::Print("[SDL_Init] is failed.");
		return false;
	}

	// Window
	mWindow = SDL_CreateWindow(Configuration::WindowTitle,
		Configuration::WindowBeginPositionX,
		Configuration::WindowBeginPositionY,
		Configuration::DisplayWidth,
		Configuration::DisplayHeight, 0);
	if (mWindow == nullptr)
	{
		ConsoleLog::Print("[SDL_CreateWindow] is failed.");
		return false;
	}

	// Surface
	mSurface = SDL_GetWindowSurface(mWindow);
	if (mSurface == nullptr)
	{
		ConsoleLog::Print("Get Surface failed.");
		return false;
	}

	return true;
}

void Display::Destroy()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Display::SwapBuffer(ColorBuffer* buffer)
{
	SDL_LockSurface(mSurface);
	std::memcpy(mSurface->pixels, buffer->GetBufferPointer(), buffer->GetBufferSize());
	SDL_UnlockSurface(mSurface);

	SDL_UpdateWindowSurface(mWindow);
}
