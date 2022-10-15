#include "card.h"

#include <string>

asw::Texture card::backImage{nullptr};
std::map<int, asw::Texture> card::faceImages{};
std::map<int, std::string> card::cardAssets = {
    {-1, "assets/img/cards/card_large_flip_-1.png"},
    {0, "assets/img/cards/card_large_flip_0.png"},
    {1, "assets/img/cards/card_large_flip_1.png"},
    {2, "assets/img/cards/card_large_flip_2.png"},
    {3, "assets/img/cards/card_large_flip_3.png"},
    {4, "assets/img/cards/card_large_flip_4.png"},
    {5, "assets/img/cards/card_large_flip_5.png"}};

// Constructor
card::card(int type, int size)
    : width(size), height(size), animationWidth(width), type(type) {
  if (backImage == nullptr) {
    backImage = asw::assets::loadTexture("assets/img/cards/card_large.png");

    for (auto const& [key, val] : cardAssets) {
      faceImages[key] = asw::assets::loadTexture(val);
    }
  }

  cardFlip = asw::assets::loadSample("assets/sfx/card_flip.wav");
  whoosh = asw::assets::loadSample("assets/sfx/whoosh.wav");
}

// Set position
void card::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

// Set selected
void card::deselect() {
  timeClicked = clock();
  selected = false;
  asw::sound::play(cardFlip);
  flipped = true;
  animationDone = false;
}

// Set matched
void card::match() {
  if (!matched) {
    matched = true;
    asw::sound::play(whoosh, 127);
  }
}

// Set card to new type
void card::setType(int type) {
  this->type = type;
}

// If selected
bool card::getSelected() const {
  return selected;
}

// Return matched
bool card::getMatched() const {
  return matched;
}

// Return type
int card::getType() const {
  return type;
}

// Return animationDone
bool card::getAnimationDone() const {
  return animationDone;
}

// Return if off the screen
bool card::getOffScreen() const {
  auto size = asw::util::getTextureSize(backImage);
  auto screenSize = asw::display::getLogicalSize();
  return x < 0 - size.x || x > screenSize.x + size.x || y < 0 - size.y ||
         y > screenSize.y + size.y;
}

// Logic
void card::logic() {
  auto screenSize = asw::display::getLogicalSize();

  if (!selected && asw::input::mouse.pressed[1] && numberSelected < 2 &&
      collision(asw::input::mouse.x, asw::input::mouse.x, x, x + width,
                asw::input::mouse.y, asw::input::mouse.y, y, y + height)) {
    timeClicked = clock();
    asw::sound::play(cardFlip);
    selected = true;
    flipped = false;
    animationDone = false;
  }

  if (matched) {
    x += x < screenSize.x / 2 ? -15 : 15;
    y += y < screenSize.y / 2 ? -15 : 15;
  }

  if (!animationDone) {
    auto timeElapsed = clock() - timeClicked;
    auto interpolation =
        static_cast<float>(timeElapsed) / static_cast<float>(CARD_FLIP_TIME_MS);
    auto widthMult = (cos(2.0f * M_PI * interpolation) + 1.0f) / 2.0f;
    animationWidth = static_cast<int>(static_cast<float>(width) * widthMult);

    if (selected) {
      if (!flipped && timeElapsed > CARD_FLIP_TIME_MS / 2) {
        flipped = true;
      } else if (flipped && timeElapsed > CARD_FLIP_TIME_MS) {
        animationDone = true;
      }
    } else {
      if (flipped && timeElapsed > CARD_FLIP_TIME_MS / 2) {
        flipped = false;
      } else if (!flipped && timeElapsed > CARD_FLIP_TIME_MS) {
        animationDone = true;
      }
    }
  } else {
    animationWidth = width;
  }
}

// Draw
void card::draw() const {
  auto& texture = flipped ? faceImages[type] : backImage;

  asw::draw::stretchSprite(texture, x + (width - animationWidth) / 2, y,
                           animationWidth, height);
}
