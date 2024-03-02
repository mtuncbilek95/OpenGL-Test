#pragma once

#include <Core/Core.h>

namespace MiniGL
{
	enum class ShaderStage
	{
		Vertex,
		Fragment,
		Compute,
		TesellationControl,
		TesellationEvaluation,
		Geometry
	};

	struct ShaderDesc
	{
		String Name;
		String Source;
		ShaderStage Stage;
		uint32 ProgramID;
	};

	class Shader
	{
	public:
		Shader(const ShaderDesc& desc);
		~Shader();

		void UseShader();

		void SetBool(const String& name, bool value) const;
		void SetInt(const String& name, int value) const;
		void SetFloat(const String& name, float value) const;
		void SetVec2(const String& name, const Vector2f& value) const;
		void SetVec3(const String& name, const Vector3f& value) const;
		void SetVec4(const String& name, const Vector4f& value) const;
		void SetMat4(const String& name, const Matrix4f& value) const;

	private:
		uint32 mShaderProgram;
		uint32 mShaderHandle;

		String mName;
		String mSource;
		ShaderStage mStage;
	};

	String ReadFile(const String& path);
	uint32 CreateProgram();
}