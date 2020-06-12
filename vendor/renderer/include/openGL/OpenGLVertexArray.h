/** \file OpenGLVertexArray.h
*/
#pragma once

#include <memory>
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"

namespace IMAT3905 {

	class OpenGLVertexArray
	{
	private:
		std::shared_ptr<OpenGLVertexBuffer> m_vertexBuffer; //!< Container for vertex buffers
		std::shared_ptr<OpenGLIndexBuffer> m_indexBuffer; //!< Index bufer for all vertex buffers
		unsigned int m_OpenGL_ID; //!< Id of the buffer in OpenGL
		unsigned int m_drawCount; //!< Number of vertice to be drawn
	public:
		OpenGLVertexArray(); //!< Constructor
		~OpenGLVertexArray(); //!< Destructor;
		void bind() const; //!< Bind the vertex array object
		void unbind() const; //!< Unbind the vertex array object
		void setVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer); //!< Add a vertex buffer
		void setIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer); //!< Set the index buffer for all vertex buffer
		std::shared_ptr<OpenGLVertexBuffer> getVertexBuffer() const; //!< Get the vertex buffers
		std::shared_ptr<OpenGLIndexBuffer> getIndexBuffer() const; //!< Get the index buffer
		inline unsigned int getDrawCount() const { return m_drawCount; }; //!< returns the number of triangles to draw
		inline unsigned int getSize() const{ return m_vertexBuffer->getSize(); }
		inline void setDrawCount(unsigned int dc) { m_drawCount = dc; }
	};
}


