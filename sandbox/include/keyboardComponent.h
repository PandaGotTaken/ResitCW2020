#pragma once
#include "IMAT3905.h"
#include "transformComponent.h"

enum class MovementDirection { Front, Back, Left, Right, None};
enum class TurnDirection {Left, Right};
enum class ControlKeys {cfront, cback, cleft, cright, rleft, rright, mfront, mback, mleft, mright};

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

	void turnPressed(TurnDirection direction) {
		switch (direction)
		{
		case TurnDirection::Left:
			lturnPressed = true;
			break;
		case TurnDirection::Right:
			rturnPressed = true;
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

	void turnReleased(TurnDirection direction) {
		switch (direction)
		{
		case TurnDirection::Left:
			lturnPressed = false;
			break;
		case TurnDirection::Right:
			rturnPressed = false;
			break;
		}
	}

	MovementDirection getDirection() { 
		velocity = { 0,0,0 };
		if (frontPressed == true) {
			return MovementDirection::Front;
			/*
			if (velocity.x < 1) {
				velocity.x += 1;
			}
			*/
		}
		if (backPressed == true) {
			return MovementDirection::Back;
/*
			if (velocity.x > -1) {
				velocity.x -= 1;
			}
			*/
		}
		if (leftPressed == true) {
			return MovementDirection::Left;
			/*
			if (velocity.z < 1) {
				velocity.z += 1;
			}
			*/
		}
		if (rightPressed == true) {
			return MovementDirection::Right;

			/*
			if (velocity.z > -1) {
				velocity.z -= 1;
			}
			*/
		}
		return MovementDirection::None;
	}

	float getTurnDirection() {
		if (lturnPressed == true) {
			return -1;
		}
		if (rturnPressed == true) {
			return 1;
		}
		return 0;
	}

	int getKey(ControlKeys key) {
		switch (key) {
		case ControlKeys::cfront:
			return cfrontkey;
			break;
		case ControlKeys::cback:
			return cbackkey;
			break;
		case ControlKeys::cleft:
			return cleftkey;
			break;
		case ControlKeys::cright:
			return crightkey;
			break;
		case ControlKeys::rleft:
			return rleftkey;
			break;
		case ControlKeys::rright:
			return rrightkey;
			break;
		case ControlKeys::mfront:
			return mfrontkey;
			break;
		case ControlKeys::mback:
			return mbackkey;
			break;
		case ControlKeys::mleft:
			return mleftkey;
			break;
		case ControlKeys::mright:
			return mrightkey;
			break;
		}
		return 0;
	}

	float getSpeed() { return m_speed; }

private:
	bool frontPressed;
	bool leftPressed;
	bool rightPressed;
	bool backPressed;
	float m_speed;
	bool lturnPressed;
	bool rturnPressed;
	int cfrontkey = SC_KEY_W, cbackkey = SC_KEY_S, cleftkey = SC_KEY_A, crightkey = SC_KEY_D, rleftkey = SC_KEY_O, rrightkey = SC_KEY_P, mfrontkey = SC_KEY_UP, mbackkey = SC_KEY_DOWN, mleftkey = SC_KEY_LEFT, mrightkey = SC_KEY_RIGHT;
	glm::vec3 velocity;
};