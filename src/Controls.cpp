#include "Controls.h"

namespace {
using asw::input::ControllerButton;
using asw::input::ControllerButtonBinding;
using asw::input::Key;
using asw::input::KeyBinding;

constexpr auto ANY = asw::input::ANY_CONTROLLER;

asw::ui::Navigation navigation_;
} // namespace

void controls::bind()
{
    // Arrows, Tab, Return, Space, Escape, D-pad, left stick, A and B
    navigation_ = asw::ui::bind_default_navigation();
    asw::input::bind_action(
        navigation_.back, ControllerButtonBinding { ControllerButton::Back, ANY });

    asw::input::bind_action(CONFIRM, KeyBinding { Key::Return });
    asw::input::bind_action(CONFIRM, ControllerButtonBinding { ControllerButton::A, ANY });
    asw::input::bind_action(CONFIRM, ControllerButtonBinding { ControllerButton::Start, ANY });
}

const asw::ui::Navigation& controls::navigation()
{
    return navigation_;
}

bool controls::any_controller_skip()
{
    return asw::input::get_controller_button_down(ANY, ControllerButton::A)
        || asw::input::get_controller_button_down(ANY, ControllerButton::B)
        || asw::input::get_controller_button_down(ANY, ControllerButton::Start);
}
