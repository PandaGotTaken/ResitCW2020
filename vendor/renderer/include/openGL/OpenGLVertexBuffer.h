/** \file OpenGLVertexBuffer.h
*/
#pragma once

#include "openGL/bufferLayout.h"
#include "openGL/OpenGLVertexBuffer.h"

namespace IMAT3905 {

	class OpenGLVertexBuffer
	{
	private:
		unsigned int m_OpenGL_ID; //!< Id of the buffer in OpenGL
		VertexBufferLayout m_layout; //!< Buffer layout;
		unsigned int m_size; //!< Size of the data stored in the buffer
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size, VertexBufferLayout& layout); //!< Constructor with buffer data and size of buffer in byte
		OpenGLVertexBuffer(void* vertices, unsigned int size, VertexBufferLayout& layout); //!< Constructor with buffer data and size of buffer in byte
		void bind(); //!< Bind the buffer
		void unbind(); //!< unbind the buffer
		void edit(float* vertices, unsigned int size, unsigned int offset); //!< Edit the contents of the buffer
		inline const VertexBufferLayout& getLayout() const { return m_layout; };
		inline unsigned int getSize() const {return m_size;}; //!< Get the size of the data stored in the VBO
		inline unsigned int id() const { return m_OpenGL_ID; }
	};

}