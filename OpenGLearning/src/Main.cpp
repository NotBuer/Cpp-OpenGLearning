#include <iostream>
#include "GameApp.hpp"

using engine::core::Application;

int main()
{
	GameApp game(engine::core::ApplicationSpecs{ .width = 1280, .height = 720, .title = "NotTerrarian" });
	game.Run();
	return 0;
}