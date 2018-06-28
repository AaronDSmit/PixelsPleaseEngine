#include "Application3D.h"
#include "FirstPersonCamera.h"

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>

#include <aie\Gizmos.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp> 

Application3D::~Application3D()
{

}

int Application3D::onStartup()
{
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	setBackgroundColour(0.25f, 0.25f, 0.25f, 1.0f);

	m_camera = new FirstPersonCamera(5.0f, 2.0f);

	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_viewMatrix = view;
	m_camera->setViewMatrix(view);

	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_camera->setProjectionMatrix(m_projectionMatrix);

	return 0;
}

void Application3D::onShutdown()
{
	delete m_camera;
	aie::Gizmos::destroy();
}

void Application3D::tick()
{
	if (glfwGetKey(getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		quit();
	}

	m_camera->tick(getWindow(), getDeltaTime());
}

void Application3D::render()
{
	// wipe the screen to the background colour
	clearScreen();

	aie::Gizmos::clear();

	aie::Gizmos::addTransform(glm::mat4(1), 5.0f);

	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0.5, 1);
	glm::vec4 yellow(1, 1, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), i == 10 ? white : black);

		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	aie::Gizmos::addSphere(glm::vec3(0), 3, 8, 8, yellow);

	aie::Gizmos::draw(m_camera->getClipSpace());
}