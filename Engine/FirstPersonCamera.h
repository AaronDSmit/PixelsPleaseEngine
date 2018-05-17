#ifndef FirstPersonCamera_H
#define FirstPersonCamera_H


#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:

	FirstPersonCamera(float a_moveSpeed, float a_rotationSpeed = glm::pi<float>() * 0.25f);
	FirstPersonCamera() = delete;
	virtual ~FirstPersonCamera();

	void tick(GLFWwindow* window, float deltaTime) override;

	float getMoveSpeed() const { return m_moveSpeed; };
	void setMoveSpeed(float a_moveSpeed) { m_moveSpeed = a_moveSpeed; };

private:
	float m_moveSpeed;
	float m_rotationSpeed;
};

#endif // !FirstPersonCamera_H