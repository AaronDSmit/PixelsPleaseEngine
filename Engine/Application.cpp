#include "Application.h"

#include <gl_core_4_4.h>
#include <GLFW/glfw3.h>
#include <aie/Gizmos.h>

#include <iostream>

Application::Application()
	: m_window(nullptr)
	, m_windowName(nullptr)
	, m_width(0)
	, m_height(0)
	, m_fullscreen(false)
	, m_gameOver(false)
	, m_startTime(std::chrono::high_resolution_clock::now())
	, m_lastFrameTime(std::chrono::high_resolution_clock::now())
	, m_elapsedTime(0.0f)
	, m_dt(0.0f)
	, m_fps(0)
{

}

Application::~Application()
{

}

int Application::run(const char * a_windowName, int a_width, int a_height, bool a_fullscreen)
{
	// start game loop if successfully initialised
	if (createWindow(a_windowName, a_width, a_height, a_fullscreen) == 0 && onStartup() == 0)
	{
		unsigned int frames = 0;
		double fpsInterval = 0.0;

		while (getRunning())
		{
			// update delta time
			auto now = std::chrono::high_resolution_clock::now();
			auto timeTaken = now - m_lastFrameTime;
			m_dt = std::chrono::duration<float>(timeTaken).count();
			m_lastFrameTime = now;
			m_elapsedTime = (now - m_startTime).count();

			// update window events (input etc)
			glfwPollEvents();

			// skip if minimised
			if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
				continue;

			// update fps every second
			frames++;
			fpsInterval += m_dt;

			if (fpsInterval >= 1.0f)
			{
				m_fps = frames;
				frames = 0;
				fpsInterval -= 1.0f;
			}

			tick();
			render();

			//present backbuffer to the monitor
			glfwSwapBuffers(m_window);

			// should the game exit?
			m_gameOver = m_gameOver || glfwWindowShouldClose(m_window) == GLFW_TRUE;
		}

		// cleanup
		onShutdown();
		shutdown();
	}

	return 0;
}

float Application::getTime() const
{
	return (float)glfwGetTime();
}

void Application::setShowCursor(bool visible)
{
	ShowCursor(visible);
}

void Application::setVSync(bool enable)
{
	glfwSwapInterval(enable ? 1 : 0);
}

void Application::setBackgroundColour(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Application::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

int Application::createWindow(const char * a_windowName, int a_width, int a_height, bool fullscreen)
{
	m_windowName = a_windowName;
	m_width = a_width;
	m_height = a_height;
	m_fullscreen = fullscreen;

	if (glfwInit() == GL_FALSE)
	{
		return -1;
	}

	m_window = glfwCreateWindow(m_width, m_height, m_windowName, (m_fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(m_window);

	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << major << "." << minor << std::endl;

	glClearColor(0, 0, 0, 1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Application::shutdown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}