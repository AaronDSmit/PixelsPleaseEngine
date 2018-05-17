#ifndef Application3D_H
#define Application3D_H

#include <Application.h>

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
	glm::mat4 m_quadTransform;
};

#endif // !Application3D_H