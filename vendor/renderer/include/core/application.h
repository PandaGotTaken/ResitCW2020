#pragma once

#include "windows/window.h"
#include <chrono>
#include <memory>

namespace IMAT3905
{
	/**
	* \class Application
	* Basic window application with timer
	*/

	class Application {
	private:
		static Application* m_instance; //!< Singleton instance
		std::shared_ptr<Window> m_window; //!< Basic window
		std::chrono::high_resolution_clock::time_point m_currentTime; //!< Current time point measured
		bool m_running = false;
		bool onClose(WindowCloseEvent& e) { shutdown(); return true; };
		bool onResize(WindowResizeEvent& e); //!< Default onResize function
		Application(); //!< private constructor - singleton
	public:
		static Application* getInstance();
		void init(const WindowProperties& props = WindowProperties()); //!< Initialise the application, opens a window
		void shutdown(); //!< Shuts the application down, closes the window
		inline bool isRunning() { return m_running; };
		float resetTimer(); //!< Reset the timer and get the time elapsed since reset timer was called in seconds
		std::shared_ptr<Window> getWindow(); //!< Returns the window
		void updateWindow(float timestep); //!< Run the swap chain and poll inputs
		void onEvent(Event& e); //!< Default onEvent which closes the window, incase on is not set
		
	};
}

#pragma once
