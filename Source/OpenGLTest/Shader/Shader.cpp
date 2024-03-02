#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

namespace MiniGL
{
	String ReadFile(const String& path)
	{
		std::ifstream file(path);

		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << path << std::endl;
			return "";
		}

		std::stringstream buffer;
		buffer << file.rdbuf();

		return buffer.str();
	}

	uint32 CreateProgram()
	{
		return glCreateProgram();
	}

	Shader::Shader(const ShaderDesc& desc) : mName(desc.Name), mShaderHandle(0), mShaderProgram(0),
		mSource(desc.Source), mStage(desc.Stage)
	{
		mShaderProgram = desc.ProgramID;

		switch (desc.Stage)
		{
		case ShaderStage::Vertex:
		{
			mShaderHandle = glCreateShader(GL_VERTEX_SHADER);
			break;
		}
		case ShaderStage::Fragment:
		{
			mShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
		case ShaderStage::Compute:
		{
			mShaderHandle = glCreateShader(GL_COMPUTE_SHADER);
			break;
		}
		case ShaderStage::TesellationControl:
		{
			mShaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
			break;
		}
		case ShaderStage::TesellationEvaluation:
		{
			mShaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
			break;
		}
		case ShaderStage::Geometry:
		{
			mShaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		}
		}

		const char* source = mSource.c_str();
		glShaderSource(mShaderHandle, 1, &source, nullptr);
		glCompileShader(mShaderHandle);

		int success;
		char infoLog[512];
		glGetShaderiv(mShaderHandle, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(mShaderHandle, 512, nullptr, infoLog);
			std::cerr << "Failed to compile shader: " << mName << std::endl;
			std::cerr << infoLog << std::endl;
		}

		glAttachShader(mShaderProgram, mShaderHandle);
		glLinkProgram(mShaderProgram);

		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);
			std::cerr << "Failed to link shader program: " << mName << std::endl;
			std::cerr << infoLog << std::endl;
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(mShaderHandle);
		glDeleteProgram(mShaderProgram);
	}

	void Shader::UseShader()
	{
		// Use the shader program
		glUseProgram(mShaderProgram);
	}

	void Shader::SetBool(const String& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(mShaderProgram, name.c_str()), static_cast<int>(value));
	}

	void Shader::SetInt(const String& name, int value) const
	{
		glUniform1i(glGetUniformLocation(mShaderProgram, name.c_str()), value);
	}

	void Shader::SetFloat(const String& name, float value) const
	{
		glUniform1f(glGetUniformLocation(mShaderProgram, name.c_str()), value);
	}

	void Shader::SetVec2(const String& name, const Vector2f& value) const
	{
		//glUniform2fv(glGetUniformLocation(mShaderProgram, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec3(const String& name, const Vector3f& value) const
	{
		//glUniform3fv(glGetUniformLocation(mShaderProgram, name.c_str()), 1, &value[0]);
	}

	void Shader::SetVec4(const String& name, const Vector4f& value) const
	{
		//glUniform4fv(glGetUniformLocation(mShaderProgram, name.c_str()), 1, &value[0]);
	}

	void Shader::SetMat4(const String& name, const Matrix4f& value) const
	{
		//glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
}