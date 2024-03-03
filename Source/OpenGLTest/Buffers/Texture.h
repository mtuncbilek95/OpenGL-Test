#pragma once

#include <Core/Core.h>

namespace MiniGL
{
	struct TextureDesc
	{
		Vector2u Size;
	};

	class Texture
	{
	public:
		Texture(const TextureDesc& desc);
		~Texture();

		void Bind() const;

	private:
		uint32 mTextureObject;
	};
}