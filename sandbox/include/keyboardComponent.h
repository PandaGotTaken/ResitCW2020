#pragma once
#include "IMAT3905.h"
#include "transformComponent.h"

enum class MovementDirection { Front, Back, Left, Right };

class KeyboardComponent
{
public:
	KeyboardComponent(TransformComponent transform) {}; //!< Construtor
	glm::vec3 m_speed;
	float move(MovementDirection direction) {
		switch (direction)
		{
		case MovementDirection::Front:
			if (m_speed.x < 1) {
				m_speed.x += 1;
			}
			break;
		case MovementDirection::Back:
			if (m_speed.x > -1) {
				m_speed.x += -1;
			}
			break;
		case MovementDirection::Left:
			if (m_speed.z > -1) {
				m_speed.z += -1;
			}
			break;
		case MovementDirection::Right:
			if (m_speed.z < 1) {
				m_speed.z += 1;
			}
			break;
		default:
			break;
		}
	}
};