#include "Intro.h"

#include <string>
#include <vector>

void Intro::init()
{
    intro_ = asw::assets::load_texture("assets/img/intro.png");
}

void Intro::update(float dt)
{
    Scene::update(dt);

    timer_ += dt;

    if (timer_ >= 3.0F || asw::input::keyboard.any_pressed) {
        manager.set_next_scene(States::Menu);
    }
}

void Intro::draw()
{
    asw::draw::sprite(intro_, asw::Vec2<float>(0, 0));
}
