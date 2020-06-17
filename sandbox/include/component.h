/** \file component.h
*/

#include <memory>
#include <typeinfo>
#include "IMAT3905.h"

#pragma once


class GameObject;

enum class ComponentMessageType {
	None = 0,
	PositionSet, RotationSet, ScaleSet,
	KeyPressed, KeyReleased
};

class ComponentMessage
{
public:
	ComponentMessage(ComponentMessageType type, void * data) : m_msgType(type), m_msgData(data) {};
	ComponentMessageType m_msgType; //!< Message type
	void * m_msgData; //!< Data associated with the message 
};

class Component
{
protected:
	GameObject* m_owner = nullptr; // Owner of the component, using a raw pointer as their is no ownership
	virtual void sendMessage(const ComponentMessage& msg);
public:
	virtual void onAttach(GameObject* owner) { m_owner = owner; };
	virtual void onDetach() { m_owner = nullptr; };
	virtual void onUpdate(float timestep) {};
	virtual void onEvent(SC::Event& e) {};
	virtual void receiveMessage(const ComponentMessage& msg) = 0;
	virtual const std::type_info& getType() = 0;
};


