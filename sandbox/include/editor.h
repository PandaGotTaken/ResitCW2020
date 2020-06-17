#pragma once
#include "IMAT3905.h"
#include "gameObject.h"
#include "proxyMeshComponent.h"
#include "transformComponent.h"
#include "colourComponent.h"

class Editor
{
public:
	void init(); //!< Initialise the editorm application
	void run();  //!< Run until closed
	void shutdown(); //!< Shutdown, free all resources
	void onEvent(SC::Event& e); //!< Event callback function
	bool onClose(SC::WindowCloseEvent& e) { SC::Application::getInstance()->shutdown(); return true; }; //!< Close the application
	bool onKeyPress(SC::KeyPressedEvent& e); //!< On a key pressed event
private:
	std::shared_ptr<SC::Application> m_application; //!< Application
	std::vector<std::shared_ptr<GameObject>> m_gameObjects; //!< Game objects in the scene
};
