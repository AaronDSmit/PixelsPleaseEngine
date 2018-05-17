#ifndef Camera_H
#define Camera_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void translate(glm::vec4 translation);

	glm::mat4& getTrasform() { return m_worldTransform; }
	const glm::mat4& getTrasform() const { return m_worldTransform; }

	void setPosition(glm::vec4 position) { m_worldTransform[3] = position; }
	glm::vec4 getPosition() const { return m_worldTransform[3]; };

	void setViewMatrix(glm::mat4 viewMatrix) { m_viewMatrix = viewMatrix; }
	glm::mat4 getViewMatrix() const { return m_viewMatrix; }

	void setProjectionMatrix(glm::mat4 projectionMatrix);
	const glm::mat4& getProjectionMatrix() const;

	glm::mat4 getClipSpace() { return m_projectionMatrix * m_viewMatrix; }

	void lookAt(glm::vec4 focusPoint, glm::vec3 up = { 0,1,0 });

	virtual void tick(struct GLFWwindow* window, float dt) {};

private:

	glm::mat4 m_worldTransform;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	bool m_hasSetProjectionMatrix;
};

#endif // !Camera_H