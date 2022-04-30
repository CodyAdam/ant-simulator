#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <Environment.h>
#include <Renderer.h>
#include <time.h>
#include <Timer.h>
#include <Agent.h>
#include <Food.h>
#include <Anthill.h>
#include <Ant.h>

static unsigned int windowWidth() { return 1024; }
static unsigned int windowHeight() { return 700; }
static float targetTPS() { return 30.0f; } // Target tick per second (TPS)
static float getSpeedModifier() { return 3.0f; };

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void onKeyPressed(char key, Environment *environment)
{
	// std::cout << "Key pressed: " << key << std::endl;
	Anthill *ah;
	switch (key)
	{
	case 'a':
		ah = new Anthill(environment, environment->randomPosition());
		for (int i = 0; i < 50; i++)
		{
			new Ant(ah, Vector2<float>(ah->getPosition() + Vector2<float>::random() * 3.0f));
		}
		break;
	case 'f':
		new Food(environment, environment->randomPosition(), MathUtils::random(200.0f, 2000.0f));
		break;
	case 'd':
		auto foods = environment->getAllInstancesOf<Food>();
		if (foods.size() > 0)
			foods[0]->setStatus(Agent::Status::destroy);
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
	Renderer *r = Renderer::getInstance();

	// Render the HUD
	Renderer::Color hudTextColor = Renderer::Color(103, 110, 114, 255);
	r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 0),
								"TPS: " + std::to_string(Timer::tps()), hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 1),
								"FPS: " + std::to_string(Timer::fps()), hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 3),
								"Controls:", hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 4),
								"A: Add Anthill", hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 5),
								"F: Add Food", hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 6),
								"D: Remove Food", hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 7),
								"Q: Quit", hudTextColor);
	r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 10),
								"Number of Agent: " + std::to_string(Agent::getAgentCount()), hudTextColor);

	Agent::render();

	r->flush();
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
	float lastUpdateIncremental = SDL_GetTicks() / 1000.0f;
	int tpsCounter = 0;
	int fpsCounter = 0;
	float lastFpsTimer = SDL_GetTicks() / 1000.0f;
	float lastTpsTimer = SDL_GetTicks() / 1000.0f;
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
			if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
			{
				onKeyPressed((char)event.key.keysym.sym, &environment);
			}
		}
		// 2 - We update the simulation
		float now = SDL_GetTicks() / 1000.0f;

		// Custom Tick Per Second system : we split the logic from the rendering
		// This allow us to have constant TPS and a more stable simulation
		// We can also change the speed of the simulation easily
		Timer::update(now - lastUpdateIncremental);
		float targetTickDuration = 1.0f / (targetTPS() * getSpeedModifier());
		// simulate only if necessary (to fit the target TPS)
		while (now - lastUpdateIncremental > targetTickDuration)
		{
			onSimulate();
			lastUpdateIncremental += targetTickDuration;
			Timer::update(0.0f); // reset the delta time

			// Update the TPS counter
			if (now - lastTpsTimer > 1.0f)
			{
				lastTpsTimer = now;
				Timer::setTps(tpsCounter);
				tpsCounter = 0;
			}
			tpsCounter++;
		}

		// 3 - We render the scene
		onRender();

		// 4 - We update the FPS counter
		if (now - lastFpsTimer > 1.0f)
		{
			lastFpsTimer = now;
			Timer::setFps(fpsCounter);
			fpsCounter = 0;
		}
		fpsCounter++;
	}

	std::cout << "Shutting down renderer..." << std::endl;
	Renderer::finalize();

	std::cout << "Shutting down agents..." << std::endl;
	Agent::finalize();

	std::cout << "Shutting down SDL" << std::endl;
	SDL_Quit();

	return 0;
}
