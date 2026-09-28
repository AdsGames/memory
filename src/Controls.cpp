#include "Controls.h"

#include <string>

namespace {
using asw::input::ControllerAxis;
using asw::input::ControllerAxisBinding;
using asw::input::ControllerButton;
using asw::input::ControllerButtonBinding;
using asw::input::Key;
using asw::input::KeyBinding;

constexpr auto ANY = asw::input::ANY_CONTROLLER;

// Stick must pass this before it counts as a direction
constexpr float STICK_THRESHOLD = 0.5F;

void bind_direction(const std::string& name, ControllerButton dpad, ControllerAxis axis, bool positive)
{
    asw::input::bind_action(name, ControllerButtonBinding { dpad, ANY });
    asw::input::bind_action(name, ControllerAxisBinding { axis, ANY, STICK_THRESHOLD, positive });
}
} // namespace

void controls::bind()
{
    bind_direction(UI_UP, ControllerButton::DPadUp, ControllerAxis::LeftY, false);
    bind_direction(UI_DOWN, ControllerButton::DPadDown, ControllerAxis::LeftY, true);
    bind_direction(UI_LEFT, ControllerButton::DPadLeft, ControllerAxis::LeftX, false);
    bind_direction(UI_RIGHT, ControllerButton::DPadRight, ControllerAxis::LeftX, true);

    asw::input::bind_action(UI_SELECT, ControllerButtonBinding { ControllerButton::A, ANY });

    asw::input::bind_action(UI_BACK, KeyBinding { Key::Escape });
    asw::input::bind_action(UI_BACK, ControllerButtonBinding { ControllerButton::B, ANY });
    asw::input::bind_action(UI_BACK, ControllerButtonBinding { ControllerButton::Back, ANY });

    asw::input::bind_action(CONFIRM, KeyBinding { Key::Return });
    asw::input::bind_action(CONFIRM, ControllerButtonBinding { ControllerButton::A, ANY });
    asw::input::bind_action(CONFIRM, ControllerButtonBinding { ControllerButton::Start, ANY });
}

void controls::update_ui(asw::ui::Root& ui)
{
    const auto move = [&ui](int dx, int dy) {
        ui.ctx.focus.focus_dir(ui.ctx, dx, dy);
        ui.ctx.theme.show_focus = true;
    };

    if (asw::input::get_action_down(UI_UP)) {
        move(0, -1);
    }
    if (asw::input::get_action_down(UI_DOWN)) {
        move(0, 1);
    }
    if (asw::input::get_action_down(UI_LEFT)) {
        move(-1, 0);
    }
    if (asw::input::get_action_down(UI_RIGHT)) {
        move(1, 0);
    }

    if (asw::input::get_action_down(UI_SELECT)) {
        ui.dispatch_to_focused(asw::ui::UIEvent { .type = asw::ui::UIEvent::Type::Activate });
    }
}

bool controls::any_controller_skip()
{
    return asw::input::get_controller_button_down(ANY, ControllerButton::A)
        || asw::input::get_controller_button_down(ANY, ControllerButton::B)
        || asw::input::get_controller_button_down(ANY, ControllerButton::Start);
}
