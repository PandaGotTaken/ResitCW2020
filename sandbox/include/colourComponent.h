#pragma once
#include "component.h"

class ColourComponent : public Component
{
public: 
	ColourComponent(const glm::vec3& colour = { 0.0,0.0,0.0 }) : m_colour(colour) {}; //!< Construtor which takes a colour value
	glm::vec3& getColour() { return m_colour; }
	const std::type_info& getType() { return typeid(ColourComponent); }
private:
	glm::vec3 m_colour;
	void receiveMessage(const ComponentMessage& msg) override {}; //!< Action when a message is received
};