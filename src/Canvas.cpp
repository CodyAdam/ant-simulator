#include <Canvas.h>

Canvas::Canvas() : WINDOW_WIDTH(1024), WINDOW_HEIGHT(700), TARGET_TPS(30.0f), speedModifier(1.0f) {}

/// <summary>
/// called each time a key is pressed.
/// </summary>
/// <param name="key">The key.</param>
/// <param name="environment">The environment.</param>
void Canvas::onKeyPressed(char key, Environment *environment)
{
  Anthill *ah;
  switch (key)
  {
  case '1':
    speedModifier = 1.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '2':
    speedModifier = 2.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '3':
    speedModifier = 3.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '4':
    speedModifier = 4.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '5':
    speedModifier = 5.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '6':
    speedModifier = 8.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '7':
    speedModifier = 10.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '8':
    speedModifier = 15.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '9':
    speedModifier = 20.0f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '0':
    speedModifier = 0.04f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '=':
    speedModifier += 0.1f;
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case '-':
    SDL_Log("-");
    speedModifier -= 0.1f;
    speedModifier = std::max(0.04f, speedModifier);
    SDL_Log("Set game speed to x%.2f", speedModifier);
    break;
  case 'a':
    SDL_Log("Spawning anthill with 50 ants");
    ah = new Anthill(environment, environment->randomPosition());
    for (int i = 0; i < 50; i++)
    {
      Vector2<float> spawnPos = ah->getPosition();
      // Vector2<float> spawnPos = environment->randomPosition();
      new SillyAnt(ah, spawnPos);
    }
    break;
  case 'f':
    SDL_Log("Spawning 3 food randomly");
    new Food(environment, environment->randomPosition(), MathUtils::random(200.0f, 2000.0f));
    new Food(environment, environment->randomPosition(), MathUtils::random(200.0f, 2000.0f));
    new Food(environment, environment->randomPosition(), MathUtils::random(200.0f, 2000.0f));
    break;
  case 'd':
    SDL_Log("Removing 1 food randomly");
    auto foods = environment->getAllInstancesOf<Food>();
    if (foods.size() > 0)
      foods[0]->setStatus(Agent::Status::destroy);
    break;
  }
}

/// <summary>
/// Called at each time step. Used only to do computation.
/// </summary>
void Canvas::onSimulate()
{
  Agent::simulate();
}

/// <summary>
/// Called at each frame. Used to render the scene.
/// </summary>
void Canvas::onRender(Environment *environment)
{
  Renderer *r = Renderer::getInstance();

  // Render the HUD
  Renderer::Color hudTextColor = Renderer::Color(103, 110, 114, 255);
  r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 0),
                "TPS: " + std::to_string(Timer::tps()) + " (x" + std::to_string((int)speedModifier) + ")", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 1),
                "FPS: " + std::to_string(Timer::fps()), hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 3),
                "Controls:", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 4),
                "A: Add Anthill", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 5),
                "F: Add 3 Foods", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 6),
                "D: Remove Food", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 7),
                "Q: Quit", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 8),
                "<1-9>: Set game speed", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 9),
                "0: Pause game", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 10),
                "-: Lower game speed", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 1, 10 + 15 * 11),
                "+: Increase game speed", hudTextColor);
  r->drawString(Vector2<float>(10 + 15 * 0, 10 + 15 * 15),
                "Number of Agent: " + std::to_string(Agent::getAgentCount()), hudTextColor);

  Agent::render();

  r->flush();
}

int Canvas::loop()
{
  // 1 - Initialization of SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS /* | SDL_INIT_AUDIO*/) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }
  // 2 - Initialization of the renderer
  Renderer::initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

  // 3 - Creation of an environment
  Environment environment(WINDOW_WIDTH, WINDOW_HEIGHT);

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
    float targetTickDuration = 1.0f / (TARGET_TPS * speedModifier);
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

    // 3 - We render the scene (max is maxFPS())

    onRender(&environment);
    // We update the FPS counter
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

Canvas::~Canvas() {}
