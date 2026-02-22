#ifndef CARD_H
#define CARD_H

#include <asw/asw.h>
#include <map>
#include <string>
#include <time.h>

#include "globals.h"

const float CARD_FLIP_TIME_S = 0.25F;

class Card {
public:
    Card(int type, float size);

    void update(float dt);
    void draw() const;

    void set_position(float x, float y);
    void deselect();
    void match();
    void set_type(int type);

    bool is_selected() const;
    bool is_animation_done() const;
    bool is_off_screen() const;
    int get_type() const;

private:
    static std::map<int, std::string> CARD_ASSETS;
    static std::map<int, asw::Texture> FACE_IMAGES;
    static asw::Texture backImage;

    asw::Sample card_flip_;
    asw::Sample whoosh_;

    asw::Quad<float> transform_;

    float animation_width_;

    int type_;

    // If selected or not
    bool selected_ { false };

    // The turning animation is done
    bool animation_done_ { true };

    // True when picture side up
    bool flipped_ { false };

    // True when a match is made
    bool matched_ { false };

    // Animation timer
    float animation_time_ {};
};

#endif
