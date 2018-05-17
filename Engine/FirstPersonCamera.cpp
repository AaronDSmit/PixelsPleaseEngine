#include "FirstPersonCamera.h"

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>

FirstPersonCamera::FirstPersonCamera(float a_moveSpeed, float a_rotationSpeed)
	:m_moveSpeed(a_moveSpeed)
	, m_rotationSpeed(a_rotationSpeed)
{

}

FirstPersonCamera::~FirstPersonCamera()
{

}

void FirstPersonCamera::tick(GLFWwindow * window, float deltaTime)
{
	if (window == nullptr) return;

	auto& forward = getTrasform()[2];
	auto& right = getTrasform()[0];
	auto& up = getTrasform()[1];

	auto wUp = glm::vec4{ 0,1,0,0 };

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(-forward * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(forward * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		translate(-right * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		translate(right * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{

		translate(wUp * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		translate(-wUp * deltaTime * m_moveSpeed);
	}
}