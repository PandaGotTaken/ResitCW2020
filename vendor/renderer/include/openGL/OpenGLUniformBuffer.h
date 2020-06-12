/** \file OpenGLUniformBuffer.h
*/
#pragma once

#include "openGL/bufferLayout.h"
#include "openGL/OpenGLShader.h"
#include <memory>

namespace IMAT3905 {

	/**
	\class OpenGLUniformBuffer
	A class for creating OpenGL Uniform Buffer Objects.
	*/

	class OpenGLUniformBuffer
	{
	private:
		unsigned int m_OpenGL_ID; //!< Id of the buffer in OpenGL
		static unsigned int s_blockNumber; //!< Next availible UBO block
		unsigned int m_blockNumber; //!< Block number which this UBO is bound to
		UniformBufferLayout m_bufferLayout; //!< Layout of the Uniform Buffer (normalised isn't used)
	public:
		OpenGLUniformBuffer(unsigned int size, UniformBufferLayout& layout); //!< Constructor where range equals size
		OpenGLUniformBuffer(unsigned int size, unsigned int rangeStart, unsigned int rangeEnd, UniformBufferLayout& layout); //!< Constructor where range is defined
		void bind(); //!< Bind the buffer
		void unbind(); //!< unbind the buffer
		void attachShaderBlock(const std::shared_ptr<OpenGLShader>& firstPassShader, const std::string& blockName); //!< Bind shader block to this buffer
		void setData(unsigned int offset, unsigned int size, void * data); //!< Set data in the buffer
		inline UniformBufferLayout getLayout() const { return m_bufferLayout; }; //!< Get the layout of this buffer
	};
}