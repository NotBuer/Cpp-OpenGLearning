#include "pch.h"
#include "EngineCore/Input.hpp"

namespace engine
{
	Input::Input(InputState* s) : _s(s) {}

	bool Input::isKeyDown(int key) const
	{
		return key >= 0 && key < (int)_s->keyDown.size() && _s->keyDown[key];
	}

	bool Input::isMouseDown(int b) const
	{
		return b >= 0 && b < (int)_s->mouseDown.size() && _s->mouseDown[b];
	}

	void Input::getMouse(double& x, double& y) const
	{
		x = _s->mouseX;
		y = _s->mouseY;
	}

	void Input::getFrameBufferSize(int& w, int& h) const
	{
		w = _s->fbWidth;
		h = _s->fbHeight;
	}

	bool Input::consumedResize() const
	{
		return _s->resized;
	}
}