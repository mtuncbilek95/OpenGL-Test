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
	desc.WindowSize = { 2560, 1440 };
	desc.Windowed = false;

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
	vShaderDesc.Source = MiniGL::ReadFile("Shaders/shader.vert");
	vShaderDesc.Name = "Vertex Shader";
	vShaderDesc.ProgramID = progID;

	MiniGL::Shader vertexShader(vShaderDesc);

	MiniGL::ShaderDesc fShaderDesc;
	fShaderDesc.Stage = MiniGL::ShaderStage::Fragment;
	fShaderDesc.Source = MiniGL::ReadFile("Shaders/shader.frag");
	fShaderDesc.Name = "Fragment Shader";
	fShaderDesc.ProgramID = progID;

	MiniGL::Shader fragmentShader(fShaderDesc);

	MiniGL::TextureDesc textureDesc;
	textureDesc.Size = desc.WindowSize;
	MiniGL::Texture texture(textureDesc);

	vertexShader.UseShader();
	fragmentShader.UseShader();

	Matrix4f model = DirectX::XMMatrixTranslationFromVector({ 0.0f, 0.0f, 0.0f });
	Matrix4f view = DirectX::XMMatrixLookAtLH({ 0.0f, 0.0f, -2.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
	Matrix4f projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), static_cast<float>(desc.WindowSize.y) / static_cast<float>(desc.WindowSize.x), 0.1f, 100.0f);

	while (!renderer.ShouldClose())
	{
		renderer.ClearColor();
		fragmentShader.SetFloat("time", glfwGetTime());
		vertexShader.SetMat4("mvp", model * view * projection);
		for (auto obj : objects)
		{
			texture.Bind();
			obj->Bind();
			renderer.Draw(obj->GetIndexCount());
		}
	}

	return 0;
}
