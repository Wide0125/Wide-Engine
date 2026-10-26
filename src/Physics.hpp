#include <glm/glm.hpp>

constexpr float GRAVITATIONAL_ACCELERATION {9.80665};

class PhysicsObject {
  public:
	PhysicsObject(
		const glm::vec3& initialPosition,
		const glm::vec3& initialVelocity,
		const glm::vec3& initialAcceleration
	)
		: m_position {initialPosition}, m_velocity {initialVelocity},
		  m_acceleration {initialAcceleration} {
		if (m_gravity) {
			m_acceleration.z += -GRAVITATIONAL_ACCELERATION;
		}
	}
	void updateObject(float seconds) {
		m_position += m_acceleration * (seconds * seconds) / 2.f + m_velocity * seconds;
		m_velocity += m_acceleration * seconds;
	}
	void setAcceleration(const glm::vec3& newAcceleration) {
		m_acceleration = newAcceleration;
		if (m_gravity) {
			m_acceleration.z += -GRAVITATIONAL_ACCELERATION;
		}
	}
	const glm::vec3& getPosition() const { return m_position; }
	const glm::vec3& getVelocity() const { return m_velocity; }
	const glm::vec3& getAcceleration() const { return m_acceleration; }
	const bool affectedByGravity() const { return m_gravity; }

  private:
	glm::vec3 m_position {};	 // in meters
	glm::vec3 m_velocity {};	 // in meters/second
	glm::vec3 m_acceleration {}; // in meters/second^2

	glm::vec3 m_previousPosition {};
	bool m_gravity {true};
};
