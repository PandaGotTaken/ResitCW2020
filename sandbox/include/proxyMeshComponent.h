#pragma once

#include <component.h>

enum class MeshType {Cuboid, Sphere, Capsule}; 

class ProxyMeshComponent : public Component
{
public:
	ProxyMeshComponent(MeshType type = MeshType::Cuboid) : m_meshType(type) {}; //!< Construtor which takes a mesh type
	MeshType& getMeshType() { return m_meshType; }
	const std::type_info& getType() { return typeid(ProxyMeshComponent); }
private:
	void receiveMessage(const ComponentMessage& msg) override {}; //!< Do nothing when a message is received
	MeshType m_meshType; //!< Internal storage for mesh type

};