#ifndef GameObject_H
#define GameObject_H

#include <aie\OBJMesh.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <aie\Shader.h>
#include <assert.h>
#include "Mesh.h"
#include <memory.h>

class GameObject
{
public:

	GameObject() {};
	GameObject(glm::mat4 a_trasform);
	GameObject(glm::mat4 a_trasform, std::shared_ptr<aie::OBJMesh> a_mesh);

	GameObject(GameObject&& other);

	// Move Constructor
	GameObject& operator= (GameObject&& other)
	{
		m_mesh = std::move(other.m_mesh);
		other.m_mesh = nullptr;

		m_transform = other.m_transform;

		return *this;
	}

	void setTransform(glm::mat4 a_transform) { m_transform = a_transform; }
	glm::mat4 getTransform() { return m_transform; }

	void setMesh(std::shared_ptr<aie::OBJMesh> a_mesh) { m_mesh = a_mesh; };
	const std::shared_ptr<aie::OBJMesh> getMesh() { return m_mesh; }

	void render(class aie::Shader& a_shader);

	~GameObject();

private:
	glm::mat4 m_transform;
	std::shared_ptr<aie::OBJMesh> m_mesh;
};

#endif // !GameObject_H