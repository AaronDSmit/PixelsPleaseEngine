#include "Camera.h"
#include <cassert>

Camera::Camera()
	: m_worldTransform(glm::mat4(1))
	, m_projectionMatrix(glm::mat4(1))
	, m_viewMatrix(glm::mat4(1))
	, m_hasSetProjectionMatrix(false)
{

}

Camera::~Camera()
{

}

void Camera::translate(glm::vec4 translation)
{
	m_worldTransform[3] += translation;
}

void Camera::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	m_hasSetProjectionMatrix = true;
	m_projectionMatrix = projectionMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	assert(m_hasSetProjectionMatrix);
	return m_projectionMatrix;
}

void Camera::lookAt(glm::vec4 focusPoint, glm::vec3 up)
{
	auto view = glm::lookAt(glm::vec3(m_worldTransform[3]), glm::vec3(focusPoint), up);
	m_worldTransform = glm::inverse(view);
}
