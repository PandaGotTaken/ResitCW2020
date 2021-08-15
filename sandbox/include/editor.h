#pragma once
#include "IMAT3905.h"
#include <entt/entt.hpp>

#include "labelComponent.h"
#include "transformComponent.h"
#include "renderComponent.h"
#include "keyboardComponent.h"
#include "AIControllerComponent.h"

class Editor
{
public:
	void init(); //!< Initialise the editorm application
	void run();  //!< Run until closed
	void shutdown(); //!< Shutdown, free all resources
	void onEvent(SC::Event& e); //!< Event callback function
	bool onClose(SC::WindowCloseEvent& e) { SC::Application::getInstance()->shutdown(); return true; }; //!< Close the application
	bool onKeyPress(SC::KeyPressedEvent& e); //!< On a key pressed event
	bool onKeyRelease(SC::KeyReleasedEvent&e); //!< On a key released event
private:
	std::shared_ptr<SC::Application> m_application; //!< Application
	entt::registry m_registry; //!< ECS registry
	std::vector<entt::entity> m_entities; //!< Game objects

};
