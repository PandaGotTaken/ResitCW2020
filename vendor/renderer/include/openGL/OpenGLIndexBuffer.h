/** \file OpenGLIndexBuffer.h
*/
#pragma once


namespace IMAT3905 {
	class OpenGLIndexBuffer
	{
	private:
		unsigned int m_OpenGL_ID; //!< Id of the buffer in OpenGL
		unsigned int m_count; //!< number of indices held in the buffer
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count); //!< Constructor with buffer data and size of buffer in byte
		void bind(); //!< Bind the buffer
		void unbind(); //!< unbind the buffer
		unsigned int getCount() const; //!< get the number of indices stored in the buffer
		void setCount(unsigned int count); //!< Set the buffer count
	};
}