#pragma once
#include <glm/glm.hpp>

enum class MeshType {Cuboid, Sphere, Capsule}; 

class RenderComponent
{
public:
	RenderComponent(MeshType type = MeshType::Cuboid, glm::vec3 colour = glm::vec3(1.f,1.f,1.f)) : m_meshType(type), m_colour(colour) {}; //!< Construtor which takes a mesh type and colour
	MeshType& getMeshType() { return m_meshType; }
	glm::vec3& getColour() { return m_colour; }
	void setMeshType(int meshIndex) { 
		
		if (meshIndex == 1) { m_meshType = MeshType::Capsule; } 
		if (meshIndex == 2) { m_meshType = MeshType::Cuboid; } 
		if (meshIndex == 3) { m_meshType = MeshType::Sphere; }
		
	}
	void setColour(glm::vec3 newColour) { m_colour = newColour; }
private:
	MeshType m_meshType; //!< Internal storage for mesh type
	glm::vec3 m_colour; //!< Tint to be applied to the mesh
};