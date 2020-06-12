/** \file inputPolling.h
*/
#pragma once

#include <glm/glm.hpp>

namespace IMAT3905 {

	/**
	\class Class for direct polling of input
	*/

	class InputPoller
	{
	public:
		static bool isKeyPressed(int keycode);  //!< Is the key with this keycode pressed
		static bool isMouseButtonPressed(int button); //!< Is this mouse button pressed
		static glm::vec2 getMousePosition(); //!< Get the current position of the mouse
		static float getMouseX(); //!< Get the current x position of the mouse
		static float getMouseY();  //!< Get the current y position of the mouse
	};

}