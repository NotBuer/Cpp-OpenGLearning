#pragma once
#include <array>
#include <cstdint>

namespace engine
{

	struct InputState
	{
		std::array<bool, 512> keyDown{};
		std::array<bool, 32> mouseDown{};
		double mouseX{ 0.0 }, mouseY{ 0.0 };
		double scrollX{ 0.0 }, scrollY{ 0.0 };
		bool resized{ false };
		int fbWidth{ 0 }, fbHeight{ 0 };
	};

	class Input
	{
	public:
		explicit Input(InputState* s);

		bool isKeyDown(int key)	const;
		bool isMouseDown(int b)	const;
		void getMouse(double& x, double& y)	const;
		void getFrameBufferSize(int& w, int& h) const;
		bool consumedResize() const;

	private:
		InputState* _s;
	};

}
