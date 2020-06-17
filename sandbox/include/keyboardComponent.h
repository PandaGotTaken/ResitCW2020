#pragma once

#include "component.h"

class KeyboardComponent : public Component
{
public:
	void receiveMessage(const ComponentMessage& msg) override {}; //!< Action when a message is received
	const std::type_info& getType() { return typeid(KeyboardComponent); }
	virtual void onUpdate(float timestep) override;
	virtual void onEvent(SC::Event& e) override;
private:
	bool onKeyPress(SC::KeyPressedEvent& e);
	bool onKeyRelease(SC::KeyReleasedEvent& e);
};