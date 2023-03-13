#include "Application.h"


#include "VulkanRenderer.h"


Application* s_Instance = nullptr;

Application::Application(std::string windowName, uint32_t width, uint32_t height)
	: m_WindowName(windowName), m_WindowWidth(width), m_WindowHeight(height)
{
	s_Instance = this;
	Init();
}

Application::~Application()
{
	Shutdown();

	s_Instance = nullptr;
}


Application& Application::Get()
{
	return *s_Instance;
}

void Application::Close()
{
}

void Application::Run()
{
	while (!glfwWindowShouldClose(m_WindowHandle))
	{
		glfwPollEvents();

		m_FrameTime= (float)glfwGetTime();
		m_TimeStep = m_FrameTime - m_LastFrameTime;
		m_LastFrameTime = m_FrameTime;

		VulkanRenderer::SceneUpdate(m_TimeStep);

		VulkanRenderer::Draw();
		std::cout << "Delta time: " << m_TimeStep << "s" << "  / FPS: " << 1.0 / m_TimeStep << std::endl;
	}

}

void Application::Init()
{
	// Initialize GLFW
	glfwInit();

	// Set GLFW to nor work with opengl
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_WindowHandle = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowName.c_str(), nullptr, nullptr);


	// Create vulkan renderer instance
	if (VulkanRenderer::Init(m_WindowHandle) == EXIT_FAILURE)
	{
		// Error to instanciate the vulkan renderer
		std::cout << " Error to instanciate the vulkan renderer\n";
	}

}

void Application::Shutdown()
{
	// destroy glfw window and stop glfw
	glfwDestroyWindow(m_WindowHandle);
	glfwTerminate();

	VulkanRenderer::CleanUp();
}
