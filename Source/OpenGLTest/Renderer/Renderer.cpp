#include "Renderer.h"

#include <iostream>
#include <glad/glad.h>

namespace MiniGL
{
	Vector2u GetCurrentResolution()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		return { static_cast<uint32>(mode->width), static_cast<uint32>(mode->height) };
	}

	Renderer::Renderer(const RendererDesc& desc) : mWindowSize(desc.WindowSize), mWindowPosition({ 0, 0 }),
		mProgramName(desc.ProgramName), mHandle(nullptr)
	{
	}

	Renderer::~Renderer()
	{
		glfwTerminate();
	}

	void Renderer::InitializeWindow()
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW" << std::endl;
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

		glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

		mHandle = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mProgramName.c_str(), nullptr, nullptr);

		if (!mHandle)
		{
			std::cerr << "Failed to create window" << std::endl;
			glfwTerminate();
			return;
		}

		Vector2u resolution = GetCurrentResolution();
		mWindowPosition = { static_cast<int>(resolution.x - mWindowSize.x) / 2, static_cast<int>(resolution.y - mWindowSize.y) / 2 };

		glfwSetWindowPos(mHandle, mWindowPosition.x, mWindowPosition.y);
		glfwMakeContextCurrent(mHandle);

		glfwShowWindow(mHandle);
	}

	void Renderer::InitializeGL()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return;
		}

		glViewport(0, 0, mWindowSize.x, mWindowSize.y);
		glfwSetFramebufferSizeCallback(mHandle, [](GLFWwindow* window, int width, int height)
			{
				glViewport(0, 0, width, height);
			});
	}
}