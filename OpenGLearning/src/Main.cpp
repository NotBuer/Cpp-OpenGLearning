#include "GameApp.hpp"

using engine::core::Application;

int main()
{
	GameApp game(engine::core::ApplicationSpecs{ .width = 800, .height = 600, .title = "NotGame" });
	game.Run();
	return 0;
}