#include "Texture.h"

#include <glad/glad.h>

namespace MiniGL
{
	Texture::Texture(const TextureDesc& desc)
	{
		glGenTextures(1, &mTextureObject);
		glBindTexture(GL_TEXTURE_2D, mTextureObject);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, desc.Size.x, desc.Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mTextureObject);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mTextureObject);
	}
}