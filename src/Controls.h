#pragma once

#include <asw/asw.h>

// Input actions shared by keyboard and controllers
namespace controls {

// Move UI focus, controller only (asw::ui::Root handles the arrow keys)
inline constexpr const char* UI_UP = "ui_up";
inline constexpr const char* UI_DOWN = "ui_down";
inline constexpr const char* UI_LEFT = "ui_left";
inline constexpr const char* UI_RIGHT = "ui_right";

// Press the focused widget, controller only (asw::ui::Root handles Return)
inline constexpr const char* UI_SELECT = "ui_select";

// Leave the current screen
inline constexpr const char* UI_BACK = "ui_back";

// Confirm the name at the end of a game
inline constexpr const char* CONFIRM = "confirm";

// Bind all actions, call once after asw::core::init
void bind();

// Move focus and press widgets in a UI with a controller
void update_ui(asw::ui::Root& ui);

// Check if a controller button that skips a screen was pressed
bool any_controller_skip();

} // namespace controls
