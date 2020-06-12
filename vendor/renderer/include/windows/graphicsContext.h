/** \file GraphicsContext.h
*/
#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"


/** \class Implementation of a graphics context for openGL and GLFW */
namespace IMAT3905
{
	class GraphicsContext
	{
	public:
		GraphicsContext(GLFWwindow* window); //!< Constructor which takes a GLFW window
		void init(); //!< Initialise the graphics context
		void swapBuffers(); //!< Swap read and write buffers - double buffering
	private:
		GLFWwindow* m_window; //!< Pointer to GLFW window
	};
}