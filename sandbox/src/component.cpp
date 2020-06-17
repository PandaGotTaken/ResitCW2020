#include "component.h"
#include "gameObject.h"


void Component::sendMessage(const ComponentMessage& msg)
{
	if (m_owner != nullptr)
	{
		auto it = m_owner->begin();
		for (; it != m_owner->end(); it++)
		{
			(*it)->receiveMessage(msg);
		}
	}
}

