#pragma once
/** \file window.h
*/


#include "graphicsContext.h"
#include "GLFW/glfw3.h"

#include "events/event.h"
#include "events/keyEvents.h"
#include "events/mouseEvents.h"
#include "events/windowsEvents.h"



namespace IMAT3905 {

	/**
	* \struct WindowProperties
	* Properties needed to set up a window
	*/

	struct WindowProperties
	{
		std::string m_title; //!< Window title
		unsigned int m_width; //!< Window width
		unsigned int m_height; //!< Window height
		bool m_isFullScreen; //!< Not currently used
		bool m_isVSync; //!< Should monitor have VSync enabled

		WindowProperties(const std::string& title = "IMAT3905", unsigned int width = 800, unsigned int height = 600, bool fullscreen = false) :
			m_title(title), m_width(width), m_height(height), m_isFullScreen(fullscreen) {}
	};

	/**
	* \class Window
	* Basic window based on GLFW
	*/

	class Window
	{
	private:
		GLFWwindow* m_nativeWindow; //!< Underlying GLFW window
		void init(const WindowProperties& properties); //!< Initialise the window with properties
		void close(); //!< Close the window
		WindowProperties m_properties; //!< Properies of the window
		std::function<void(Event&)>  m_callback; //!< General OnEvent callback 
		float m_aspectRatio; //!< Aspect ratio on creation
		std::shared_ptr<GraphicsContext> m_context; //!< Graphics context and swapchain
	public:
	
		Window() {};
		Window(const WindowProperties& properties); //!< Constructor with initial properties
		~Window(); //!< Destructor
		void onUpdate(float timestep); //!< Update every timestep, perfor4ms double buffering
		void onResize(unsigned int width, unsigned int height); //!< Resize the window including restencilling
		void setVSync(bool VSync); //!< Set monitor VSync
		void setEventCallback(const std::function<void(Event&)>& callback); //!< Set the callback function for this window
		unsigned int getWidth() const; //!< Returns the window width including stencilled background
		unsigned int getHeight() const; //!< Returns the window width including stencilled background
		GLFWwindow* getGLFWWindow() const; //!< Returns the underlying GLFW window
		bool isFullScreenMode() const; //!< Returns whether full screen mode is enabled, not currently used
		bool isVSync() const; //!< Is the monitor in VSync mode
	};
}