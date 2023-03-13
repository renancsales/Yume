#pragma once

#include "KeyCodes.h"

#include "Application.h"

#include <GLFW/glfw3.h>

class Input
{
public:
	static bool IsKeyPressed(KeyCode keycode);
	static bool IsMouseButtonPressed(MouseButton button);

	static void GetMousePosition(float& x, float& y);

	static void SetCursorMode(CursorMode mode);
};

