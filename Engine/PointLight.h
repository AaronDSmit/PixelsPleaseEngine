#ifndef PointLight_H
#define PointLight_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class PointLight
{
public:

	PointLight()
		: m_position({ 0.0f, 0.0f, 0.0f })
		, m_diffuse({ 0.25f, 0.25f, 0.25f })
		, m_specular({ 1.0f, 1.0f, 1.0f })
		, m_ambientLight({ 1.0f, 1.0f, 1.0f })
		, m_constant(1.0f)
		, m_linear(1.0f)
		, m_quadratic(1.0f)
		, m_intensity(1.0f)
	{ };

	// white point light at a position
	PointLight(glm::vec3 a_position)
		: PointLight()
	{
		m_position = a_position;
	}

	~PointLight() {};

	void setAmbient(glm::vec3 a_ambient) { m_ambientLight = a_ambient; };
	const glm::vec3 getAmbient() const { return m_ambientLight; };

	void setDiffuse(glm::vec3 a_diffuse) { m_diffuse = a_diffuse; };
	const glm::vec3 getDiffuse() const { return m_diffuse; };

	void setSpecular(glm::vec3 a_specular) { m_specular = a_specular; };
	const glm::vec3 getSpecular() const { return m_specular; };

	void setPosition(glm::vec3  a_position) { m_position = a_position; };
	const glm::vec3 getPosition() const { return m_position; };

	void setConstant(float a_constant) { m_constant = a_constant; };
	const float getConstant() const { return m_constant; };

	void setLinear(float a_linear) { m_linear = a_linear; };
	const float getLinear() const { return m_linear; };

	void setQuadratic(float a_quadratic) { m_quadratic = a_quadratic; };
	const float getQuadratic() const { return m_quadratic; };

	void setIntensity(float a_intensity) { m_intensity = a_intensity; };
	const float getIntensity() const { return m_intensity; };

private:
	glm::vec3 m_position;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_ambientLight;

	float m_constant;
	float m_linear;
	float m_quadratic;
	float m_intensity;
};

#endif // !PointLight_H