#include "InputBox.h"

InputBox::InputBox(int x, int y, int width, int height, asw::Font font, const std::string& value,
    const std::string& type)
    : x(x)
    , y(y)
    , width(width)
    , height(height)
    , font(font)
    , text(value)
    , type(type)
{
}

void InputBox::focus()
{
    focused = true;
}

std::string InputBox::getValue() const
{
    return text;
}

bool InputBox::hover() const
{
    return asw::input::mouse.position.x > x && asw::input::mouse.position.x < x + width
        && asw::input::mouse.position.y > y && asw::input::mouse.position.y < y + height;
}

void InputBox::update()
{
    // Focus
    if (asw::input::mouse.pressed[1]) {
        focused = hover();

        if (focused) {
            int closest = width;

            for (unsigned int i = 0; i <= text.length(); i++) {
                const int textSize = asw::util::get_text_size(font, text.substr(0, i)).x;
                const int distance = std::abs(textSize + x + 6 - asw::input::mouse.position.x);

                if (distance < closest) {
                    textIterator = i;
                    closest = distance;
                }
            }
        }
    }

    int lastKey = asw::input::keyboard.last_pressed;

    if (!focused || lastKey == -1) {
        return;
    }

    // a character key was pressed; add it to the string
    if (type == "number" || type == "text") {
        // Numeric only
        if (lastKey >= 30 && lastKey <= 38) {
            text.insert(text.begin() + textIterator, lastKey + 19);
            textIterator++;
        }

        if (lastKey == 39) {
            text.insert(text.begin() + textIterator, lastKey + 9);
            textIterator++;
        }
    }

    if (type == "text" && lastKey >= 4 && lastKey <= 29) {
        if (asw::input::get_key_down(asw::input::Key::LShift)
            || asw::input::get_key_down(asw::input::Key::RShift)) {
            text.insert(text.begin() + textIterator, 'A' - 4 + lastKey);
        } else {
            text.insert(text.begin() + textIterator, 'a' - 4 + lastKey);
        }

        textIterator++;
    }

    // some other, "special" key was pressed; handle it here
    if (asw::input::get_key_down(asw::input::Key::Backspace) && textIterator != 0) {
        textIterator--;
        text.erase(text.begin() + textIterator);
    }

    if (asw::input::get_key_down(asw::input::Key::Right) && textIterator != text.size()) {
        textIterator++;
    }

    if (asw::input::get_key_down(asw::input::Key::Left) && textIterator != 0) {
        textIterator--;
    }
}

// Draw box
void InputBox::draw() const
{
    asw::draw::rect_fill(asw::Quad<float>(x, y, width, height), asw::Color(12, 12, 12));

    asw::Color col = (hover() || focused) ? asw::Color(230, 230, 230) : asw::Color(245, 245, 245);

    if (focused) {
        asw::draw::rect_fill(asw::Quad<float>(x + 2, y + 2, width - 4, height - 4), col);
    } else {
        asw::draw::rect_fill(asw::Quad<float>(x + 1, y + 1, width - 2, height - 2), col);
    }

    // Output the string to the screen
    asw::draw::text(font, text, asw::Vec2<float>(x + 6, y), asw::Color(22, 22, 22));

    // Draw the caret
    if (focused) {
        int textSize = asw::util::get_text_size(font, text.substr(0, textIterator)).x;

        asw::draw::rect_fill(
            asw::Quad<float>(textSize + x + 6, y + 8, 1, height - 16), asw::Color(0, 0, 0));
    }
}
