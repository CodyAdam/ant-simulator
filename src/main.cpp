#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Environment.h>
#include <Renderer.h>
#include <time.h>
#include <Timer.h>
#include <Agent.h>
#include <Food.h>

static unsigned int windowWidth() { return 1024; }
static unsigned int windowHeight() { return 700; }
static float targetTPS() { return 10.0f; } // Target tick per second (TPS)
static float getTPS() { return 1 / Timer::dt(); }

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment *environment)
{
	std::cout << "Key pressed: " << key << std::endl;
	switch (key)
	{
	case 'f':
		// add a new food on the environment
		new Food(environment, environment->randomPosition(), 100.0f);
		break;
	}
}

/// <summary>
/// Called at each time step. Used only to do computation.
/// </summary>
void onSimulate()
{
	Agent::simulate();
}

/// <summary>
/// Called at each frame. Used to render the scene.
/// </summary>
void onRender()
{
	// draw a string on the top left corner that says "TPS: xxx"
	Renderer::getInstance()->drawString(Vector2<float>(10, 10), "TPS: " + std::to_string(getTPS()), Renderer::Color(103, 110, 114, 255));
	Renderer::getInstance()->flush();
}

/// <summary>
/// The main program.
/// </summary>
/// <param name="argc">The number of arguments.</param>
/// <param name="argv">The arguments.</param>
/// <returns></returns>
int main(int /*argc*/, char ** /*argv*/)
{
	// 1 - Initialization of SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS /* | SDL_INIT_AUDIO*/) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}
	// 2 - Initialization of the renderer
	Renderer::initialize(windowWidth(), windowHeight());

	// 3 - Creation of an environment
	Environment environment(windowWidth(), windowHeight());

	// 4 - We change the seed of the random number generator
	srand((unsigned int)time(NULL));

	// The main event loop...
	SDL_Event event;
	bool exit = false;
	float lastTime = 0.0f;
	while (!exit)
	{
		// 1 - We handle events
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == 'q'))
			{
				::std::cout << "Exit signal detected" << ::std::endl;
				exit = true;
				break;
			}
			if (event.type == SDL_KEYDOWN)
			{
				onKeyPressed((char)event.key.keysym.sym, &environment);
			}
		}
		float nowTime = SDL_GetTicks() / 1000.0f;
		Timer::update(nowTime - lastTime);
		// 2 - We update the simulation

		// simulate only if necessary (to fit the target TPS)
		if (Timer::dt() > 1.0f / targetTPS())
		{
			lastTime = nowTime;
			onSimulate();
		}
		onRender();
	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();

	std::cout << "Shutting down agents..." << std::endl;
	Agent::finalize();

	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
