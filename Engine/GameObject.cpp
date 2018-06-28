#include "GameObject.h"

#include <aie\Shader.h>

GameObject::GameObject(glm::mat4 a_trasform)
	: m_transform(a_trasform)
{

}

GameObject::GameObject(glm::mat4 a_trasform, std::shared_ptr<aie::OBJMesh> a_mesh)
	: GameObject(a_trasform)
{
	m_mesh = a_mesh;
}

GameObject::GameObject(GameObject && other)
{

	m_mesh = std::move(other.m_mesh);

	m_transform = other.m_transform;
}

void GameObject::render(aie::Shader& a_shader)
{
	if (m_mesh != nullptr)
	{
		m_mesh->draw();
	}
}

GameObject::~GameObject()
{

}
