#pragma once

#include "openGL/ShaderDataTypes.h"
#include "openGL/bufferLayout.h"

#include <glad/glad.h>
#include <string>
#include <map>

namespace IMAT3905
{
	/**
	\class OpenGLShader
	An interface class for creating OpenGL shader programmes.
	*/

	using UniformLayout = std::map<std::string, void *>;

	class OpenGLShader
	{
	public:
		OpenGLShader(const std::string& source); //!< constructor with combined source code as a string
		inline unsigned int id() { return m_OpenGL_ID; } //!< Get the API id of the shader programme
		void bind(); //!< Bind the shader
		void unbind(); //!< Unbind the shader
		bool uploadData(const std::string& name, void * data); //!< Upload data to the GPU
		bool uploadData(const UniformLayout& uniforms); //!< Upload a group of data to the GPU
		inline VertexBufferLayout getBufferLayout() const { return m_bufferLayout; }
		inline UniformLayout getUniformLayout() const { return m_uniformLayout; }
		bool uploadSamplers(const std::string& name, int count, int * data);
	private:
		unsigned int m_OpenGL_ID; //!< Shader ID
		void parseSource(const std::string& filepath); //!< Parse the source code seperating into different shader source files. Parse for uniforms, compile, link and cache uniform information
		void compileAndLink(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc); //Compile and link vertex and fragment shader. Can be expanded to other source types
		void dispatchUniformUpload(ShaderDataType type, GLuint location, void * data); //Dispatches uniform uploads
		std::map <std::string, std::pair<ShaderDataType, GLuint>> m_uniformCache; //!< Caches uniform types and locations
		VertexBufferLayout m_bufferLayout; //!< Layout of the vertex buffer as read from the shader file
		UniformLayout m_uniformLayout; //!< Data map that can be uploaded to this shader
	};
}