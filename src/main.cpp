/*Memory
  Allan Legemaate
  28/08/13
*/

// Includes
#include <asw/asw.h>
#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>
#include <chrono>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

// For state engine
#include "State.h"
#include "globals.h"

using namespace std::chrono_literals;
using namespace std::chrono;
constexpr nanoseconds timestep(16ms);

// State engine
StateEngine* game_state;

// Functions
void setup();
void draw();
void update();

// FPS system
int fps = 0;
int frames_done = 0;

// Setup game
void setup() {
  // Load allegro library
  asw::util::init(1280, 960);

  game_state = new StateEngine();
}

// Update
void update() {
  // Update listeners
  KeyListener::update();
  MouseListener::update();

  asw::core::update();

  // Do state logic
  game_state->update();

  // Handle exit
  if (game_state->getStateId() == StateEngine::STATE_EXIT) {
    asw::core::exit = true;
  }
}

// Do state rendering
void draw() {
  game_state->draw();
}

// Loop (emscripten compatibility)
#ifdef __EMSCRIPTEN__
void loop() {
  update();
  draw();
}
#endif

// Main function*/
int main(int argc, char* argv[]) {
  // Setup basic functionality
  setup();

  // Set the current state ID
  game_state->setNextState(StateEngine::STATE_INIT);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#else

  using clock = high_resolution_clock;
  nanoseconds lag(0ns);
  auto time_start = clock::now();

  while (!KeyListener::keyDown[SDL_SCANCODE_ESCAPE] && !asw::core::exit) {
    auto delta_time = clock::now() - time_start;
    time_start = clock::now();
    lag += duration_cast<nanoseconds>(delta_time);

    while (lag >= timestep) {
      lag -= timestep;
      update();
    }

    draw();
    frames_done++;
  }
#endif

  return 0;
}
