#pragma once
#include "IMAT3905.h"
#include "transformComponent.h"

enum class MovementDirection { Front, Back, Left, Right };

class KeyboardComponent
{
public:
	KeyboardComponent(float speed = 1) : m_speed(speed) {}; //!< Construtor
	void directionPressed(MovementDirection direction) {
		switch (direction)
		{
		case MovementDirection::Front:
			frontPressed = true;
			break;
		case MovementDirection::Back:
			backPressed = true;
			break;
		case MovementDirection::Left:
			leftPressed = true;
			break;
		case MovementDirection::Right:
			rightPressed = true;
			break;
		default:
			break;
		}
	}

	void directionReleased(MovementDirection direction) {
		switch (direction)
		{
		case MovementDirection::Front:
			frontPressed = false;
			break;
		case MovementDirection::Back:
			backPressed = false;
			break;
		case MovementDirection::Left:
			leftPressed = false;
			break;
		case MovementDirection::Right:
			rightPressed = false;
			break;
		default:
			break;
		}
	}

	glm::vec3& getDirection() { 
		velocity = { 0,0,0 };
		if (frontPressed == true) {
			if (velocity.x < 1) {
				velocity.x += 1;
			}
		}
		if (backPressed == true) {
			if (velocity.x > -1) {
				velocity.x -= 1;
			}
		}
		if (leftPressed == true) {
			if (velocity.z < 1) {
				velocity.z += 1;
			}
		}
		if (rightPressed == true) {
			if (velocity.z > -1) {
				velocity.z -= 1;
			}
		}
		return (velocity * m_speed);
	}

	float getSpeed() { return m_speed; }

private:
	bool frontPressed;
	bool leftPressed;
	bool rightPressed;
	bool backPressed;
	float m_speed;
	glm::vec3 velocity;
};