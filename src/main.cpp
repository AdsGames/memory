/*Memory
  Allan Legemaate
  28/08/13
*/

// Includes
#include <asw/asw.h>

// For state engine
#include "Game.h"
#include "HighScores.h"
#include "Init.h"
#include "Intro.h"
#include "LevelSelect.h"
#include "Menu.h"
#include "State.h"

// Main function*/
int main() {
  asw::core::init(1280, 960);

  auto app = asw::scene::SceneManager<States>();
  app.registerScene<Init>(States::Init, app);
  app.registerScene<Intro>(States::Intro, app);
  app.registerScene<Menu>(States::Menu, app);
  app.registerScene<LevelSelect>(States::LevelSelect, app);
  app.registerScene<Game>(States::Game, app);
  app.registerScene<HighScores>(States::HighScores, app);
  app.setNextScene(States::Init);

  app.start();

  return 0;
}
