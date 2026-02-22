#include "Init.h"

#include <asw/asw.h>

void Init::init()
{
    asw::display::set_title("Setting up");
    asw::display::set_icon("assets/img/icon.png");
    asw::display::set_title("Memory");
}

void Init::update(float dt)
{
    Scene::update(dt);

    manager.set_next_scene(States::Intro);
}

void Init::draw()
{
    asw::draw::clear_color(asw::Color(0, 0, 0));
}
