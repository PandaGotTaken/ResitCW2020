#pragma once

#include "component.h"

class AIControllerComponent : public Component
{
public:
	virtual void onUpdate(float timestep) override;
	virtual void receiveMessage(const ComponentMessage& msg) override;
	const std::type_info& getType() { return typeid(AIControllerComponent); }
private:

};