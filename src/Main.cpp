#include "Engine.h"

int main(int argc, char** argv)
{
	Engine& engine = Engine::Instance();

	if (engine.Initialize())
	{
		engine.Update();
	}
	engine.Destroy();

	return 0;
}