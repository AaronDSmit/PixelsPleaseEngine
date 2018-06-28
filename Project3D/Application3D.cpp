#include "Application3D.h"
#include "FirstPersonCamera.h"

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>

#include <aie/Gizmos.h>
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
	m_camera->setViewMatrix(view);

	glm::mat4 m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, (float)getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);
	m_camera->setProjectionMatrix(m_projectionMatrix);

	//Load shader compiles the shaders and gives it to the graphics card
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return -1;
	}

	if (m_soulspearMesh.load("./objects/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}

	m_soulspearTransform =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	m_lighting = std::make_unique<Lighting>();

	m_lighting->addDirectionalLight({ 0, 0, 0 }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
	m_lighting->addDirectionalLight({ 1, 1, 1 }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.2f, 0.2f }, { 0.25f, 0.25f, 0.25f });

	return 0;
}

void Application3D::onShutdown()
{
	// m_lighting deleted via smart pointer
	// m_objects deleted via smart pointer
	delete m_camera;
	aie::Gizmos::destroy();
}

void Application3D::tick()
{
	if (glfwGetKey(getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		quit();
	}

	// query time since application started
	float time = getTime();

	// rotate light
	m_lighting->getDirectionalLight(0)->setDirection(glm::normalize(glm::vec3(0.0f, glm::sin(time), glm::cos(time))));

	m_lighting->getDirectionalLight(1)->setDirection(glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0)));

	m_camera->tick(getWindow(), getDeltaTime());
}

void Application3D::render()
{
	// wipe the screen to the background colour
	clearScreen();

	// bind shader
	m_shader.bind();

	// bind transform
	m_shader.bindUniform("ProjectionViewModel", m_camera->getProjectionView() * m_soulspearTransform);

	m_shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_soulspearTransform)));

	m_shader.bindUniform("ModelMatrix", m_soulspearTransform);

	for (int i = 0; i < m_lighting->getDirectionalCount(); i++)
	{
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_direction").c_str(), m_lighting->getDirectionalLight(i)->getDirection());
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_ambient").c_str(), m_lighting->getDirectionalLight(i)->getAmbient());
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_diffuse").c_str(), m_lighting->getDirectionalLight(i)->getDiffuse());
		m_shader.bindUniform(("lights[" + std::to_string(i) + "].m_specular").c_str(), m_lighting->getDirectionalLight(i)->getSpecular());
	}

	m_shader.bindUniform("HasTextures", 1);

	m_shader.bindUniform("cameraPosition", m_camera->getPosition());

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	// draw mesh
	m_soulspearMesh.draw();

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

	for (int i = 0; i < m_lighting->getDirectionalCount(); i++)
	{
		aie::Gizmos::addAABBFilled(m_lighting->getDirectionalLight(i)->getDirection(), glm::vec3(0.1, 0.1, 0.1), glm::vec4(m_lighting->getDirectionalLight(i)->getDiffuse().x, m_lighting->getDirectionalLight(i)->getDiffuse().y, m_lighting->getDirectionalLight(i)->getDiffuse().z, 1.0f));
	}

	glEnable(GL_DEPTH_TEST);

	aie::Gizmos::draw(m_camera->getClipSpace());
}