/** \file Camera.h
*/
#pragma once

#include <glm/glm.hpp>

namespace IMAT3905 {
	class Camera
	{
	public:
		Camera();
		const glm::mat4& getView() const;
		const glm::mat4& getProjection() const;
		void forward();
		void back();
		void left();
		void right();
		void up();
		void down();
	private:
		void updateView();
		glm::mat4 m_view;
		glm::mat4 m_projection;
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_right;
		glm::vec3 m_up;
		float m_distanceFromCentre = 10.f;
		float m_pitch = 0.f;
		const float m_minDistance = 0.25f;
		const float m_minPitch = -1.2f;
		const float m_maxPitch = 1.2f;
		const float m_linearSpeed = 0.1f;
		const float m_angularSpeed = 0.05f;
	};
}