#pragma once

#include <asw/asw.h>

// Input actions shared by keyboard and controllers
namespace controls {

// Confirm the name at the end of a game
inline constexpr const char* CONFIRM = "confirm";

// Bind all actions, call once after asw::core::init
void bind();

// UI navigation actions, set on asw::ui::Root::ctx.navigation
const asw::ui::Navigation& navigation();

// Check if a controller button that skips a screen was pressed
bool any_controller_skip();

} // namespace controls
