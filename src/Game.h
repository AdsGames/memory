#pragma once

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
class Game : public asw::scene::Scene<States> {
 public:
  using asw::scene::Scene<States>::Scene;

  void init() override;

  void update(float deltaTime) override;

  void draw() override;

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
