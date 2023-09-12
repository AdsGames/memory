#include "Card.h"

#include <string>

asw::Texture Card::backImage{nullptr};
std::map<int, asw::Texture> Card::faceImages{};
std::map<int, std::string> Card::cardAssets = {
    {-1, "assets/img/cards/card_large_flip_-1.png"},
    {0, "assets/img/cards/card_large_flip_0.png"},
    {1, "assets/img/cards/card_large_flip_1.png"},
    {2, "assets/img/cards/card_large_flip_2.png"},
    {3, "assets/img/cards/card_large_flip_3.png"},
    {4, "assets/img/cards/card_large_flip_4.png"},
    {5, "assets/img/cards/card_large_flip_5.png"}};

// Constructor
Card::Card(int type, int size)
    : width(size), height(size), animationWidth(width), type(type) {
  if (backImage == nullptr) {
    backImage = asw::assets::loadTexture("assets/img/cards/card_large.png");

    for (auto const& [key, val] : cardAssets) {
      faceImages[key] = asw::assets::loadTexture(val);
    }
  }

  cardFlip = asw::assets::loadSample("assets/sfx/card_flip.wav");
  whoosh = asw::assets::loadSample("assets/sfx/whoosh.wav");
  animationTime.start();
}

// Set position
void Card::setPosition(int x, int y) {
  this->x = x;
  this->y = y;
}

// Set selected
void Card::deselect() {
  animationTime.reset();
  selected = false;
  asw::sound::play(cardFlip);
  flipped = true;
  animationDone = false;
}

// Set matched
void Card::match() {
  if (!matched) {
    matched = true;
    asw::sound::play(whoosh, 127);
  }
}

// Set card to new type
void Card::setType(int type) {
  this->type = type;
}

// If selected
bool Card::isSelected() const {
  return selected;
}

// Return matched
bool Card::getMatched() const {
  return matched;
}

// Return type
int Card::getType() const {
  return type;
}

// Return animationDone
bool Card::isAnimationDone() const {
  return animationDone;
}

// Return if off the screen
bool Card::isOffScreen() const {
  auto size = asw::util::getTextureSize(backImage);
  auto screenSize = asw::display::getLogicalSize();
  return x < 0 - size.x || x > screenSize.x + size.x || y < 0 - size.y ||
         y > screenSize.y + size.y;
}

// Logic
void Card::logic() {
  auto screenSize = asw::display::getLogicalSize();

  if (!selected && asw::input::mouse.pressed[1] && numberSelected < 2 &&
      collision(asw::input::mouse.x, asw::input::mouse.x, x, x + width,
                asw::input::mouse.y, asw::input::mouse.y, y, y + height)) {
    animationTime.reset();
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
    auto timeElapsed =
        animationTime.getElapsedTime<std::chrono::milliseconds>();

    auto interpolation = timeElapsed / CARD_FLIP_TIME_MS;
    auto widthMult = (cos(2.0f * M_PI * interpolation) + 1.0f) / 2.0f;
    animationWidth = static_cast<int>(static_cast<float>(width) * widthMult);

    if (selected) {
      if (!flipped && timeElapsed > CARD_FLIP_TIME_MS / 2.0) {
        flipped = true;
      } else if (flipped && timeElapsed > CARD_FLIP_TIME_MS) {
        animationDone = true;
      }
    } else {
      if (flipped && timeElapsed > CARD_FLIP_TIME_MS / 2.0) {
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
void Card::draw() const {
  auto& texture = flipped ? faceImages[type] : backImage;

  asw::draw::stretchSprite(texture, x + (width - animationWidth) / 2, y,
                           animationWidth, height);
}
