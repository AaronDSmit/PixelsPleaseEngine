#include "FirstPersonCamera.h"

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning( pop )

#include <iostream>

FirstPersonCamera::FirstPersonCamera(float a_moveSpeed, float a_rotationSpeed)
	:m_moveSpeed(a_moveSpeed)
	, m_rotationSpeed(a_rotationSpeed)
	, m_mouseX(0.0)
	, m_mouseY(0.0)
	, m_mouseDown(false)
{

}

FirstPersonCamera::~FirstPersonCamera()
{

}

void FirstPersonCamera::tick(GLFWwindow* window, float deltaTime)
{
	if (window == nullptr) return;

	processKeyboardInput(window, deltaTime);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		if (!m_mouseDown) // first frame the mouse button is pressed down
		{
			glfwGetCursorPos(window, &m_mouseClickX, &m_mouseClickY);
			m_mouseDown = true;

			std::cout << "Mouse first Pressed" << std::endl;
		}
		else
		{
			processMouseInput(window, deltaTime);
		}
	}
	else
	{
		m_mouseDown = false;
	}
}

void FirstPersonCamera::processKeyboardInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		translate(-m_forward * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		translate(m_forward * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		translate(-m_right * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		translate(m_right * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		translate(m_worldUp * deltaTime * m_moveSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		translate(-m_worldUp * deltaTime * m_moveSpeed);
	}
}

void FirstPersonCamera::processMouseInput(GLFWwindow* window, float deltaTime)
{
	int windowWidth, windowHeight; // Get the width and height from the window
	glfwGetWindowSize(window, &windowWidth, &windowHeight);

	glfwGetCursorPos(window, &m_mouseX, &m_mouseY);

	double percentMovedX = glm::abs(m_mouseClickX - m_mouseX) / windowWidth;
	double percentMovedY = glm::abs(m_mouseClickY - m_mouseY) / windowHeight;

	double mouseDeltaX = m_prevMouseX - m_mouseX;
	double mouseDeltaY = m_prevMouseY - m_mouseY;

	if (glm::abs(m_mouseX - m_mouseClickX) > 5 && mouseDeltaX != 0)
	{
		float moveDir = (m_mouseX > m_mouseClickX) ? -5.0f : 5.0f;

		if (moveDir > 0)
		{
			moveDir *= (mouseDeltaX < 0) ? -1 : 1;
		}
		else
		{
			moveDir *= (mouseDeltaX > 0) ? -1 : 1;
		}

		glm::vec4 up = getViewMatrix() * glm::vec4(0, 1, 0, 0);
		glm::mat4 rotMatrix(1.0f);

		rotMatrix = glm::rotate(rotMatrix, moveDir * m_rotationSpeed * deltaTime, glm::vec3(up[0], up[1], up[2]));
		getTransform() *= rotMatrix;
	}

	if (glm::abs(m_mouseY - m_mouseClickY) > 5 && mouseDeltaY != 0)
	{
		float moveDir = (m_mouseY > m_mouseClickY) ? -5.0f : 5.0f;

		if (moveDir > 0)
		{
			moveDir *= (mouseDeltaY < 0) ? -1 : 1;
		}
		else
		{
			moveDir *= (mouseDeltaY > 0) ? -1 : 1;
		}

		glm::mat4 rotMatrix(1.0f);

		rotMatrix = glm::rotate(rotMatrix, moveDir * m_rotationSpeed * deltaTime, glm::vec3(1, 0, 0));
		getTransform() *= rotMatrix;
	}

	m_prevMouseX = m_mouseX;
	m_prevMouseY = m_mouseY;

	glm::mat4 oldTrans = getTransform();

	glm::mat4 trans;

	glm::vec3 worldUp = glm::vec3(0, 1, 0);

	//Right
	glm::vec3 oldForward = glm::vec3(oldTrans[2].x, oldTrans[2].y, oldTrans[2].z);

	trans[0] = glm::normalize(glm::vec4(glm::cross(worldUp, oldForward), 0));
	//Up
	glm::vec3 newRight = glm::vec3(trans[0].x, trans[0].y, trans[0].z);
	trans[1] = glm::normalize(glm::vec4(glm::cross(oldForward, newRight), 0));
	//Forward
	trans[2] = glm::normalize(oldTrans[2]);

	//Position
	trans[3] = oldTrans[3];

	setTransform(trans);
}