#include "transformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

void TransformComponent::calculateTransform()
{
	auto t = glm::translate(glm::mat4(1.0f), m_position);
	auto rx = glm::rotate(m_rotation.x, glm::vec3(1.f,0.f,0.f));
	auto ry = glm::rotate(m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
	auto rz = glm::rotate(m_rotation.z, glm::vec3(0.f, 0.f, 1.f));
	auto r = rx * ry * rz;
	auto s = glm::scale(m_scale);
	m_transform = t * r *s;
}

void TransformComponent::receiveMessage(const ComponentMessage & msg)
{
}
