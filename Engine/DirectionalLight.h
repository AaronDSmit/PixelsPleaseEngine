#ifndef DirectionalLight_H
#define DirectionalLight_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class DirectionalLight
{
public:

	// Default Constructor
	DirectionalLight()
		:m_direction({ 1.0f, 1.0f, 1.0f })
		, m_diffuse({ 0.25f, 0.25f, 0.25f })
		, m_specular({ 1.0f, 1.0f, 1.0f })
		, m_ambientLight({ 1.0f, 1.0f, 1.0f })
	{};

	// white light with direction
	DirectionalLight(glm::vec3 a_direction)
		: DirectionalLight()
	{
		m_direction = a_direction;
	};

	// full set-up
	DirectionalLight(glm::vec3 a_direction, glm::vec3 a_diffuse, glm::vec3 a_specular, glm::vec3 a_ambientLight)
		: m_direction(a_direction)
		, m_diffuse(a_diffuse)
		, m_specular(a_specular)
		, m_ambientLight(a_ambientLight)
	{};

	const glm::vec3 getDirection() const { return m_direction; };

	//angle in radians
	void setDirection(glm::vec3 a_direction)
	{
		m_direction = glm::normalize(a_direction);
	};

	void setAmbient(glm::vec3 a_ambient) { m_ambientLight = a_ambient; };
	const glm::vec3 getAmbient() const { return m_ambientLight; };

	void setDiffuse(glm::vec3 a_diffuse) { m_diffuse = a_diffuse; };
	const glm::vec3 getDiffuse() const { return m_diffuse; };

	void setSpecular(glm::vec3 a_specular) { m_specular = a_specular; };
	const glm::vec3 getSpecular() const { return m_specular; };

	~DirectionalLight() {};

private:
	glm::vec3 m_direction;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_ambientLight;
};

#endif // !DirectionalLight_H