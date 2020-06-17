#include "gameObject.h"

void GameObject::addComponent(const std::shared_ptr<Component>& comp)
{
	m_components.push_back(comp);
	comp->onAttach(this);
}

void GameObject::removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter)
{
	(*iter)->onDetach();
	m_components.erase(iter);
}

void GameObject::onUpdate(float timestep)
{
	for (auto& comp : m_components)
	{
		comp->onUpdate(timestep);
	}
}

void GameObject::onEvent(SC::Event & e)
{
	for (auto& comp : m_components)
	{
		if (!e.handled())
		{
			comp->onEvent(e);
		}
	}
}