#ifndef GAME_H
#define GAME_H

#include <asw/asw.h>
#include <string>
#include <vector>

#include "State.h"
#include "button.h"
#include "card.h"

// Intro screen of game
class Game : public State {
 public:
  explicit Game(StateEngine& engine) : State(engine) {}

  virtual void init() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void cleanup() override{};

  void addScore(const std::string& name);

 private:
  asw::Texture background;
  asw::Font font;

  int moves{0};

  std::vector<card> cards;

  std::string edittext = "";
  std::string::iterator iter = edittext.begin();
};

#endif  // GAME_H
