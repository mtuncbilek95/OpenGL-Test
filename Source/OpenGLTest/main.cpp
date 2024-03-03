#include <Renderer/Renderer.h>
#include <Shader/Shader.h>
#include <Buffers/Buffer.h>
#include <Buffers/Texture.h>

#include <math.h>

Array<MiniGL::Vertex> vertices = {
	{ { -1.0f, -1.0f, 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f } },
	{ { -1.0f,  1.0f, 0.0f }, {0.0f, 1.0f, 0.0f, 1.0f}, { 0.0f, 1.0f } },
	{ {  1.0f,  1.0f, 0.0f }, {0.0f, 0.0f, 1.0f, 1.0f}, { 1.0f, 1.0f } },
	{ {  1.0f, -1.0f, 0.0f }, {0.0f, 1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f } }
};

Array<uint32> indices = {
	0, 1, 3,
	1, 2, 3
};

Array<MiniGL::Buffer*> objects;

int main()
{
	MiniGL::RendererDesc desc;
	desc.ProgramName = "OpenGL Test";
	desc.WindowSize = { 1920, 1080 };

	MiniGL::Renderer renderer(desc);
	renderer.InitializeWindow();
	renderer.InitializeGL();

	MiniGL::BufferDesc bufferDesc;
	bufferDesc.Vertices = vertices;
	bufferDesc.Indices = indices;
	objects.push_back(new MiniGL::Buffer(bufferDesc));

	uint32 progID = MiniGL::CreateProgram();

	MiniGL::ShaderDesc vShaderDesc;
	vShaderDesc.Stage = MiniGL::ShaderStage::Vertex;
	vShaderDesc.Source = MiniGL::ReadFile(R"(D:\Projects\OpenGL-Test\Source\Shaders\shader.vert)");
	vShaderDesc.Name = "Vertex Shader";
	vShaderDesc.ProgramID = progID;

	MiniGL::Shader vertexShader(vShaderDesc);

	MiniGL::ShaderDesc fShaderDesc;
	fShaderDesc.Stage = MiniGL::ShaderStage::Fragment;
	fShaderDesc.Source = MiniGL::ReadFile(R"(D:\Projects\OpenGL-Test\Source\Shaders\shader.frag)");
	fShaderDesc.Name = "Fragment Shader";
	fShaderDesc.ProgramID = progID;

	MiniGL::Shader fragmentShader(fShaderDesc);

	MiniGL::Texture texture;

	vertexShader.UseShader();
	fragmentShader.UseShader();

	while (!renderer.ShouldClose())
	{
		renderer.ClearColor();
		fragmentShader.SetFloat("time", glfwGetTime());
		fragmentShader.SetVec2("resolution", { 1920, 1080 });
		for (auto obj : objects)
		{
			texture.Bind();
			obj->Bind();
			renderer.Draw(obj->GetIndexCount());
		}
	}

	return 0;
}
