#include "Lighting.h"

#include <assert.h>

Lighting::Lighting()
	: m_currentDirIndex(0)
	, m_currentPointIndex(0)
{
	m_dirLights.reserve(5);
}

void Lighting::addDirectionalLight(glm::vec3 a_direction)
{
	auto dl = std::make_shared<DirectionalLight>(a_direction);

	m_dirLights.push_back(dl);
}

void Lighting::addDirectionalLight(glm::vec3 a_direction, glm::vec3 a_diffuse, glm::vec3 a_specular, glm::vec3 a_ambientLight)
{
	auto dl = std::make_shared<DirectionalLight>(a_direction, a_diffuse, a_specular, a_ambientLight);

	m_dirLights.push_back(dl);
}

void Lighting::addPointLight()
{
	auto pl = std::make_shared<PointLight>();

	m_pointLights.push_back(pl);
}

void Lighting::addPointLight(glm::vec3 a_position)
{
	auto pl = std::make_shared<PointLight>(a_position);

	m_pointLights.push_back(pl);
}

std::shared_ptr<DirectionalLight> Lighting::getDirectionalLight(int a_index)
{
	assert(a_index < m_dirLights.size());

	return m_dirLights[a_index];
}

std::shared_ptr<DirectionalLight> Lighting::getNextDirectionalLight()
{
	if (m_currentDirIndex < m_dirLights.size() - 1)
	{
		m_currentDirIndex++;
		return m_dirLights[m_currentDirIndex - 1];
	}

	m_currentDirIndex = 0;
	return nullptr;
}

std::shared_ptr<PointLight> Lighting::getPointLight(int a_index)
{
	assert(a_index < m_dirLights.size());

	return m_pointLights[a_index];
}

std::shared_ptr<PointLight> Lighting::getNextPointLight()
{
	if (m_currentPointIndex < m_pointLights.size() - 1)
	{
		m_currentPointIndex++;
		return m_pointLights[m_currentPointIndex - 1];
	}

	m_currentPointIndex = 0;
	return nullptr;
}

Lighting::~Lighting()
{
	// m_dirLights deleted via smart pointer
	// m_pointLights deleted via smart pointer
}