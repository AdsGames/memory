#ifndef GAME_H
#define GAME_H

#include <asw/asw.h>
#include <string>
#include <vector>

#include "GameDifficulty.h"
#include "State.h"
#include "card.h"
#include "ui/InputBox.h"
#include "util/ScoreManager.h"

// Intro screen of game
class Game : public State {
 public:
  using State::State;

  void init() override;
  void update() override;
  void draw() override;
  void cleanup() override{
      // Nothing to do
  };

  static GameDifficulty difficulty;

 private:
  std::string getScoresFile() const;

  asw::Texture background;
  asw::Font font;

  int moves{0};

  std::vector<card> cards;

  InputBox nameBox;

  ScoreManager scoreManager;

  int cardSelected1{0};
  int cardSelected2{0};
};

#endif  // GAME_H
