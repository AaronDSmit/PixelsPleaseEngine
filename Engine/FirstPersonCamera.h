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

	void setMoveSpeed(float a_moveSpeed) { m_moveSpeed = a_moveSpeed; };
	float getMoveSpeed() const { return m_moveSpeed; };


private:

	void processKeyboardInput(GLFWwindow* window, float deltaTime);
	void processMouseInput(GLFWwindow* window, float deltaTime);

private:
	
	float m_moveSpeed;
	float m_rotationSpeed;

	double m_mouseClickX;
	double m_mouseClickY;

	double m_prevMouseX;
	double m_prevMouseY;

	double m_mouseX;
	double m_mouseY;

	bool m_mouseDown;
	bool m_fastMode;
};

#endif // !FirstPersonCamera_H