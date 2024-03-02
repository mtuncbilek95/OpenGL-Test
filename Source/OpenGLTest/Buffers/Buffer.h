#pragma once

#include <Core/Core.h>

namespace MiniGL
{
	struct Vertex
	{
		XMFLOAT3 Position;
	};

	struct BufferDesc
	{
		Array<Vertex> Vertices;
		Array<uint32> Indices;
	};

	class Buffer
	{
	public:
		Buffer(const BufferDesc& desc);
		~Buffer();

		void Bind() const;

		const uint32& GetIndexCount() const { return mIndexCount; }

	private:
		uint32 mBufferObject;
		uint32 mArrayObject;
		uint32 mElementObject;
		uint32 mIndexCount;
	};
}