#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <mutex>
#include <numbers>
#include <shared_mutex>


#include <glm/glm.hpp>

class Camera {
  public:
	Camera(const glm::vec3& position = {}, const glm::vec2& gazeAngles = {})
		: m_position {position}, m_gazeAngles {gazeAngles} {}

	void moveCameraPosition(const glm::vec3& delta) {
		m_position += delta;
	}
	void moveCameraGaze(const glm::vec2& deltaAngles) {
		m_gazeAngles += deltaAngles;
		m_lookingUp = false;
		m_lookingDown = false;
		if (m_gazeAngles.y > std::numbers::pi / 2) {
			m_gazeAngles.y = std::numbers::pi / 2;
			m_lookingUp = true;
		} else if (m_gazeAngles.y < -std::numbers::pi / 2) {
			m_gazeAngles.y = std::numbers::pi / -2;
			m_lookingDown = true;
		}
		if (m_gazeAngles.x > std::numbers::pi * 2) {
			m_gazeAngles.x = std::fmod(m_gazeAngles.x, std::numbers::pi * 2);
		}
		if (m_gazeAngles.x < 0) {
			m_gazeAngles.x = std::numbers::pi * 2 - m_gazeAngles.x;
		}
	}
	const glm::vec3& getCameraPosition() {
		return m_position;
	}
	const glm::vec2& getGazeAngles() {
		return m_gazeAngles;
	}
	const glm::vec3 getLookAtVector() {
		glm::vec3 elevationVector {0, 0, sin(m_gazeAngles.y)};
		glm::vec3 azimuthVector {
			cos(m_gazeAngles.y) * cos(m_gazeAngles.x), cos(m_gazeAngles.y) * sin(m_gazeAngles.x), 0
		};
		return azimuthVector + elevationVector;
	}
	const glm::vec3 getUp() {
		if (m_lookingDown) {
			return {cos(m_gazeAngles.x), sin(m_gazeAngles.x), 0};
		} else if (m_lookingUp) {
			return -glm::vec3 {cos(m_gazeAngles.x), sin(m_gazeAngles.x), 0};
		}
		return m_up;
	}

  private:
	glm::vec3 m_position {};
	glm::vec2 m_gazeAngles {};
	glm::vec3 m_up {0, 0, 1};

	bool m_lookingUp {false};
	bool m_lookingDown {false};
};

#endif
