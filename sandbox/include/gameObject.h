#pragma once

#include <vector>
#include "component.h"
#include "IMAT3905.h"


class GameObject
{
protected:
	std::string m_name; //!< For debug purposes
	std::vector<std::shared_ptr<Component>> m_components;
public:
	GameObject(const std::string& name) : m_name(name) {}
	void onUpdate(float timestep);
	void onEvent(SC::Event& e);
	void addComponent(const std::shared_ptr<Component>& comp);
	void removeComponent(std::vector<std::shared_ptr<Component>>::iterator iter);
	template<typename G>
	std::vector<std::shared_ptr<Component>>::iterator getComponent()
	{
		auto result = m_components.end();
		for (auto it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (it->get()->getType().hash_code() == typeid(G).hash_code()) return it;
		}

		return result;
	}

	inline std::vector<std::shared_ptr<Component>>::iterator begin() { return m_components.begin(); }
	inline std::vector<std::shared_ptr<Component>>::iterator end() { return m_components.end(); }
	inline unsigned int componentCount() { return m_components.size(); }
	inline const std::string& name() { return m_name; }
};
