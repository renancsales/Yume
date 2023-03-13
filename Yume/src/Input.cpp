#include "Input.h"

bool Input::IsKeyPressed(KeyCode keycode)
{
	// Get window handle
	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();

	int state = glfwGetKey(windowHandle, (int)keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(MouseButton button)
{
	// Get window handle
	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();

	int state = glfwGetMouseButton(windowHandle, (int)button);
	return state == GLFW_PRESS;
}

void Input::GetMousePosition(float& x, float& y)
{
	// Get window handle
	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();

	double xpos, ypos;
	glfwGetCursorPos(windowHandle, &xpos, &ypos);
	x = (float)xpos; y = (float)ypos;
}

void Input::SetCursorMode(CursorMode mode)
{
	// Get window handle
	GLFWwindow* windowHandle = Application::Get().GetWindowHandle();

	glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
}
