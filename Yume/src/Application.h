#pragma once
#define STB_IMAGE_IMPLEMENTATION
#define GLFW_FORCE_DEPTH_ZERO_TO_ONE

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>


class Application
{
public:
	Application(std::string windowName, uint32_t width, uint32_t height);
	~Application();

	GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }
	
	static Application& Get();

	void Close();
	
	void Run();

private:
	void Init();
	void Shutdown();

public:
	// Scene
	GLFWwindow* m_WindowHandle = nullptr;
	// Application specifications
	uint32_t m_WindowWidth = 800 , m_WindowHeight = 600;
	std::string m_WindowName;

	float m_TimeStep = 0.0f;
	float m_FrameTime = 0.0f;
	float m_LastFrameTime = 0.0f;
};