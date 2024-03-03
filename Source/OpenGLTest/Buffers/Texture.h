#pragma once

#include <Core/Core.h>

namespace MiniGL
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		void Bind() const;

	private:
		uint32 mTextureObject;
	};
}