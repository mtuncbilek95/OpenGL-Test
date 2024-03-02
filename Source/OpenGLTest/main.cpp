#include <Renderer/Renderer.h>

int main()
{
	MiniGL::RendererDesc desc;
	desc.ProgramName = "OpenGL Test";
	desc.WindowSize = { 1280, 720 };

	MiniGL::Renderer renderer(desc);
	renderer.InitializeWindow();
	renderer.InitializeGL();

	while (!renderer.ShouldClose())
	{
		glfwPollEvents();
	}

	return 0;
}
