#include "Card.h"

#include <numbers>
#include <string>

asw::Texture Card::backImage { nullptr };
std::map<int, asw::Texture> Card::FACE_IMAGES {};
std::map<int, std::string> Card::CARD_ASSETS = { { -1, "assets/img/cards/card_large_flip_-1.png" },
    { 0, "assets/img/cards/card_large_flip_0.png" },
    { 1, "assets/img/cards/card_large_flip_1.png" },
    { 2, "assets/img/cards/card_large_flip_2.png" },
    { 3, "assets/img/cards/card_large_flip_3.png" },
    { 4, "assets/img/cards/card_large_flip_4.png" },
    { 5, "assets/img/cards/card_large_flip_5.png" } };

// Constructor
Card::Card(int type, float size)
    : animation_width_(size)
    , type_(type)
{
    transform_.size.x = size;
    transform_.size.y = size;

    if (backImage == nullptr) {
        backImage = asw::assets::load_texture("assets/img/cards/card_large.png");

        for (auto const& [key, val] : CARD_ASSETS) {
            FACE_IMAGES[key] = asw::assets::load_texture(val);
        }
    }

    card_flip_ = asw::assets::load_sample("assets/sfx/card_flip.wav");
    whoosh_ = asw::assets::load_sample("assets/sfx/whoosh.wav");
}

// Set position
void Card::set_position(float x, float y)
{
    transform_.position.x = x;
    transform_.position.y = y;
}

// Set selected
void Card::deselect()
{
    animation_time_ = 0.0F;
    selected_ = false;
    asw::sound::play(card_flip_);
    flipped_ = true;
    animation_done_ = false;
}

// Set matched
void Card::match()
{
    if (!matched_) {
        matched_ = true;
        asw::sound::play(whoosh_, 0.5F);
    }
}

// Set card to new type
void Card::set_type(int type)
{
    this->type_ = type;
}

// If selected
bool Card::is_selected() const
{
    return selected_;
}

// Return type
int Card::get_type() const
{
    return type_;
}

// Return animationDone
bool Card::is_animation_done() const
{
    return animation_done_;
}

// Return if off the screen
bool Card::is_off_screen() const
{
    const auto size = asw::util::get_texture_size(backImage);
    const auto screen_size = asw::display::get_logical_size();

    return transform_.position.x < 0 - size.x || transform_.position.x > screen_size.x + size.x
        || transform_.position.y < 0 - size.y || transform_.position.y > screen_size.y + size.y;
}

// Logic
void Card::update(float dt)
{
    auto screen_size = asw::display::get_logical_size();

    if (!selected_ && asw::input::mouse.pressed[1] && number_selected < 2
        && transform_.contains(asw::input::mouse.position)) {
        animation_time_ = 0.0F;
        asw::sound::play(card_flip_);
        selected_ = true;
        flipped_ = false;
        animation_done_ = false;
    }

    if (matched_) {
        transform_.position.x += transform_.position.x < screen_size.x / 2 ? -15 : 15;
        transform_.position.y += transform_.position.y < screen_size.y / 2 ? -15 : 15;
    }

    if (!animation_done_) {
        animation_time_ += dt;
        auto interpolation = animation_time_ / CARD_FLIP_TIME_S;
        auto widthMult = (cos(2.0F * std::numbers::pi_v<float> * interpolation) + 1.0F) / 2.0F;
        animation_width_ = transform_.size.x * widthMult;

        if (selected_) {
            if (!flipped_ && interpolation > 0.5F) {
                flipped_ = true;
            } else if (flipped_ && interpolation > 1.0F) {
                animation_done_ = true;
            }
        } else {
            if (flipped_ && interpolation > 0.5F) {
                flipped_ = false;
            } else if (!flipped_ && interpolation > 1.0F) {
                animation_done_ = true;
            }
        }
    } else {
        animation_width_ = transform_.size.x;
    }
}

// Draw
void Card::draw() const
{
    const auto& texture = flipped_ ? FACE_IMAGES[type_] : backImage;

    const auto x_offset = (transform_.size.x - animation_width_) / 2.0F;

    asw::draw::stretch_sprite(texture,
        asw::Quad<float>(transform_.position.x + x_offset, transform_.position.y, animation_width_,
            transform_.size.y));
}
