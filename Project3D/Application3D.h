#ifndef Application3D_H
#define Application3D_H

#include <Application.h>
#include <aie/Shader.h>
#include <Mesh.h>
#include <aie/OBJMesh.h>

#include <glm/glm.hpp>

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
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	aie::ShaderProgram m_shader;
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
};

#endif // !Application3D_H