#include "Buffer.h"

#include <glad/glad.h>

namespace MiniGL
{
	Buffer::Buffer(const BufferDesc& desc) : mBufferObject(0), mArrayObject(0), mElementObject(0), mIndexCount(desc.Indices.size())
	{
		glGenBuffers(1, &mBufferObject);
		glGenBuffers(1, &mElementObject);
		glBindBuffer(GL_ARRAY_BUFFER, mBufferObject);
		glBufferData(GL_ARRAY_BUFFER, desc.Vertices.size() * sizeof(Vertex), desc.Vertices.data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &mArrayObject);
		glBindVertexArray(mArrayObject);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.Indices.size() * sizeof(uint32), desc.Indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, sizeof(Vertex::Position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex::Position), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &mBufferObject);
		glDeleteVertexArrays(1, &mArrayObject);
		glDeleteBuffers(1, &mElementObject);
	}
	void Buffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementObject);
		glBindVertexArray(mArrayObject);
	}
}