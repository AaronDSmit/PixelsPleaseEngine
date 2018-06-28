#ifndef Camera_H
#define Camera_H

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4310 )
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#pragma warning( pop )

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void translate(glm::vec4 translation);

	void setTransform(glm::mat4 a_transform) { m_worldTransform = a_transform; }
	glm::mat4& getTransform() { return m_worldTransform; }
	const glm::mat4& getTransform() const { return m_worldTransform; }

	void setPosition(glm::vec4 position) { m_worldTransform[3] = position; }
	glm::vec4 getPosition() const { return m_worldTransform[3]; };

	void setViewMatrix(glm::mat4 a_viewMatrix);
	glm::mat4 getViewMatrix() const;

	void setProjectionMatrix(glm::mat4 projectionMatrix);
	const glm::mat4& getProjectionMatrix() const;

	glm::mat4 getClipSpace() { return m_projectionMatrix * getViewMatrix(); }

	void lookAt(glm::vec4 focusPoint, glm::vec3 up = { 0,1,0 });

	virtual void tick(struct GLFWwindow* window, float dt) {};

	glm::vec4& m_forward = m_worldTransform[2];
	glm::vec4& m_right = m_worldTransform[0];
	glm::vec4& m_up = m_worldTransform[1];
	glm::vec4 m_worldForward = glm::vec4(0, 0, -1, 0);
	glm::vec4 m_worldRight = glm::vec4(1, 0, 0, 0);
	glm::vec4 m_worldUp = glm::vec4(0, 1, 0, 0);

private:

	glm::mat4 m_worldTransform;
	glm::mat4 m_projectionMatrix;

	bool m_hasSetProjectionMatrix;
	bool m_hasSetViewMatrix;
};

#endif // !Camera_H