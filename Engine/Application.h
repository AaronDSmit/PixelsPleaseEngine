#ifndef Application_H
#define Application_H

#include <chrono>

struct GLFWwindow;


// this is the pure-virtual base class that wraps up an application for us.
// we derive our own applications from this class
class Application
{
public:
	Application();
	virtual ~Application();

	// creates a window and begins the game loop which calls tick() and render() repeatedly
	// it first calls onStartup() and if that succeeds it then starts the loop,
	// ending with onShutdown() if m_gameOver is true
	int run(const char* a_windowName, int a_width, int a_height, bool a_fullscreen);

	virtual void tick() = 0;
	virtual void render() = 0;
	virtual int onStartup() = 0;
	virtual void onShutdown() = 0;

	// returns the width / height of the game window
	int getWindowWidth() { return m_width; }
	int getWindowHeight() { return m_height; }

	const char* getWindowName() { return m_windowName; }

	// access to the GLFW window
	GLFWwindow* getWindow() { return m_window; }

	// returns the frames-per-second that the loop is running at
	unsigned int getFPS() const { return m_fps; }

	// returns the time in seconds it took to complete the last frame
	float getDeltaTime() { return m_dt; }

	// returns time since application started
	float getTime() const;

	// show or hide the OS cursor
	void setShowCursor(bool visible);

	// enable or disable v-sync
	void setVSync(bool enable);

	// sets m_gameOver to true which will close the application safely when the frame ends
	void quit() { m_gameOver = true; }

protected:

	// sets the colour that the screen is cleared to
	void setBackgroundColour(float r, float g, float b, float a = 1.0f);

	// wipes the screen clear to begin a frame of drawing
	void clearScreen();

private:

	bool getRunning() const { return !m_gameOver; }
	int createWindow(const char* a_windowName, int a_width, int a_height, bool fullscreen);
	void shutdown();

private:

	GLFWwindow * m_window;
	const char* m_windowName;
	int m_width;
	int m_height;
	bool m_fullscreen;

	// if set to false, the main game loop will exit
	bool m_gameOver;

	std::chrono::high_resolution_clock::time_point m_startTime;
	std::chrono::high_resolution_clock::time_point m_lastFrameTime;
	float m_elapsedTime;
	float m_dt;
	unsigned int m_fps;
};

#endif // !Application_H