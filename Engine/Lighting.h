#ifndef Lighting_H
#define Lighting_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <memory>
#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"

class Lighting
{
public:
	Lighting();

	void addDirectionalLight(glm::vec3 a_direction);
	void addDirectionalLight(glm::vec3 a_direction, glm::vec3 a_diffuse, glm::vec3 a_specular, glm::vec3 a_ambientLight);

	void addPointLight();
	void addPointLight(glm::vec3 a_position);

	std::shared_ptr<DirectionalLight> getDirectionalLight(int a_index);
	std::shared_ptr<DirectionalLight> getNextDirectionalLight();

	void setDirectionalIndex(int a_index) { m_currentDirIndex = a_index; }
	const int getDirectionalCount() const { return m_dirLights.size(); }

	std::shared_ptr<PointLight> getPointLight(int a_index);
	std::shared_ptr<PointLight> getNextPointLight();

	void setPointIndex(int a_index) { m_currentPointIndex = a_index; }
	const int getPointCount() const { return m_pointLights.size(); }

	~Lighting();

private:
	std::vector<std::shared_ptr<DirectionalLight>> m_dirLights;
	std::vector<std::shared_ptr<PointLight>> m_pointLights;

	int m_currentDirIndex;
	int m_currentPointIndex;
};

#endif // !Lighting_H
