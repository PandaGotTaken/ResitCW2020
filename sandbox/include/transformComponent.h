#pragma once

#include "component.h"

class TransformComponent : public Component
{
public:
	TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) :
		m_position(position), m_rotation(rotation), m_scale(scale)
	{calculateTransform();}; //!< Construtor which takes position, scale and rotation
	const glm::mat4& getTransform() { return m_transform; } //!< Accessor for transform
	const glm::vec3& getPosition() { return m_position; } //!< Accessor for  position
	const glm::vec3& getRotation() { return m_rotation; } //!< Accessor for rotation
	const glm::vec3& getScale() { return m_scale; } //!< Accessor for scale
	const std::type_info& getType() { return typeid(TransformComponent); }
private:
	glm::mat4 m_transform; 
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	void calculateTransform();
	void receiveMessage(const ComponentMessage& msg) override; //!< Action when a message is received
};

