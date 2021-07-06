#pragma once
#include <glm/glm.hpp>

enum class MeshType {Cuboid, Sphere, Capsule}; 

class RenderComponent
{
public:
	RenderComponent(MeshType type = MeshType::Cuboid, glm::vec3 colour = glm::vec3(1.f,1.f,1.f)) : m_meshType(type), m_colour(colour) {}; //!< Construtor which takes a mesh type and colour
	MeshType& getMeshType() { return m_meshType; }
	glm::vec3& getColour() { return m_colour; }
private:
	MeshType m_meshType; //!< Internal storage for mesh type
	glm::vec3 m_colour; //!< Tint to be applied to the mesh
};