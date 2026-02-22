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
int main()
{
    asw::core::init(1280, 960);

    auto app = asw::scene::SceneManager<States>();
    app.register_scene<Init>(States::Init, app);
    app.register_scene<Intro>(States::Intro, app);
    app.register_scene<Menu>(States::Menu, app);
    app.register_scene<LevelSelect>(States::LevelSelect, app);
    app.register_scene<Game>(States::Game, app);
    app.register_scene<HighScores>(States::HighScores, app);
    app.set_next_scene(States::Init);
    app.start();

    return 0;
}
