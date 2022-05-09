#ifndef _CANVAS_H
#define _CANVAS_H

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
#include <AntWithRules.h>
#include <SillyAnt.h>
#include <chrono>
#include <thread>

class Canvas
{
private:
  const unsigned int WINDOW_WIDTH;
  const unsigned int WINDOW_HEIGHT;

  // Target tick per second (TPS) if time speed is x1.
  const float TARGET_TPS;
  float speedModifier;

public:
  Canvas();

  /// <summary>
  /// called each time a key is pressed.
  /// </summary>
  /// <param name="key">The key.</param>
  /// <param name="environment">The environment.</param>
  void onKeyPressed(char key, Environment *environment);

  /// <summary>
  /// Called at each time step. Used only to do computation.
  /// </summary>
  void onSimulate();

  /// <summary>
  /// Called at each frame. Used to render the scene.
  /// </summary>
  void onRender(Environment *environment);

  int loop();

  ~Canvas();
};

#endif