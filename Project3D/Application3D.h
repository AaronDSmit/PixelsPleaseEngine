#ifndef Application3D_H
#define Application3D_H

#include <Application.h>
#include <aie/Shader.h>
#include <Mesh.h>
#include <aie/OBJMesh.h>

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include <GameObject.h>
#include <Lighting.h>

class Application3D : public Application
{
public:
	Application3D() : Application() {}
	virtual ~Application3D();

	virtual int onStartup() override;
	virtual void onShutdown() override;
	virtual void tick() override;
	virtual void render() override;

protected:

	class FirstPersonCamera* m_camera;

	aie::ShaderProgram m_shader;

	//Soul Spear
	aie::OBJMesh m_soulspearMesh;
	glm::mat4 m_soulspearTransform;
	aie::Texture m_soulspearTexture;

	std::vector<std::unique_ptr<GameObject>> m_objects;

	std::unique_ptr<Lighting> m_lighting;
};

#endif // !Application3D_H