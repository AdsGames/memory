#ifndef GAME_H
#define GAME_H

#include <asw/asw.h>
#include <map>
#include <string>
#include <vector>

#include "Card.h"
#include "GameDifficulty.h"
#include "State.h"
#include "ui/InputBox.h"
#include "util/ScoreManager.h"

struct DifficultyConfig {
  std::string highscoresFile;
  int dimension;
};

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
  static std::map<GameDifficulty, DifficultyConfig> DIFFICULTY_CONFIG;

  void initCards(const DifficultyConfig& config);
  void eraseOffScreenCards();
  void matchCards();
  void calculateSelectedCards();
  void endgameUpdate();

  asw::Texture background;
  asw::Font font;

  int moves{0};

  std::vector<Card> cards;

  InputBox nameBox;

  ScoreManager scoreManager;

  unsigned int cardSelected1{0};
  unsigned int cardSelected2{0};
};

#endif  // GAME_H
