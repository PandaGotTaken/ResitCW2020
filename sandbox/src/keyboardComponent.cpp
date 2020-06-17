#include "keyboardComponent.h"
#include "events/eventCodes.h"
#include "ImGuiHelper.h"

void KeyboardComponent::onUpdate(float timestep)
{
	if (SC::InputPoller::isKeyPressed(SC_KEY_LEFT)) ImGuiHelper::writeToConsole("OnUpdate: Left button pressed");
	if (SC::InputPoller::isKeyPressed(SC_KEY_RIGHT)) ImGuiHelper::writeToConsole("OnUpdate: Right button pressed");
}

void KeyboardComponent::onEvent(SC::Event & e)
{
	SC::EventDispatcher dispatcher(e);
	dispatcher.dispatch<SC::KeyPressedEvent>(std::bind(&KeyboardComponent::onKeyPress, this, std::placeholders::_1));
	dispatcher.dispatch<SC::KeyReleasedEvent>(std::bind(&KeyboardComponent::onKeyRelease, this, std::placeholders::_1));
}

bool KeyboardComponent::onKeyPress(SC::KeyPressedEvent & e)
{
	if (e.GetKeyCode() == SC_KEY_UP)
	{
		ImGuiHelper::writeToConsole("OnKeyPress: Up button pressed");
		return true;
	}
	else if (e.GetKeyCode() == SC_KEY_DOWN)
	{
		ImGuiHelper::writeToConsole("OnKeyPress: Down button pressed");
		return true;
	}
	return false;
}

bool KeyboardComponent::onKeyRelease(SC::KeyReleasedEvent & e)
{
	if (e.GetKeyCode() == SC_KEY_UP)
	{
		ImGuiHelper::writeToConsole("OnKeyPress: Up button released");
		return true;
	}
	else if (e.GetKeyCode() == SC_KEY_DOWN)
	{
		ImGuiHelper::writeToConsole("OnKeyPress: Down button released");
		return true;
	}
	return false;
}
