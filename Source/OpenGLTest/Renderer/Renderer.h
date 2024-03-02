#pragma once

#include <Core/Core.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace MiniGL
{
	struct RendererDesc
	{
		String ProgramName;
		Vector2u WindowSize;
	};

	class Renderer
	{
	public:
		Renderer(const RendererDesc& desc);
		~Renderer();

		void InitializeWindow();
		void InitializeGL();

		void ClearColor();
		void Draw(uint32 index);

		GLFWwindow* GetWindowHandle() const { return mHandle; }
		bool ShouldClose() const { return glfwWindowShouldClose(mHandle); }

	private:
		GLFWwindow* mHandle;
		Vector2u mWindowSize;
		String mProgramName;
		Vector2i mWindowPosition;
	};
}