#include "Game.h"

#include <asw/util/KeyListener.h>
#include <asw/util/MouseListener.h>
#include <fstream>

#include "globals.h"

void Game::init() {
  background = asw::load::texture("assets/img/backgrounds/background.png");

  font = asw::load::font("assets/fonts/ariblk.ttf", 24);

  // Creates 10 blank cards
  for (int i = 0; i < difficulty; i++) {
    for (int t = 0; t < difficulty; t++) {
      card newCard(i * 800 / difficulty + 250, t * 800 / difficulty + 80, -1,
                   700 / difficulty);
      cards.push_back(newCard);
    }
  }

  // Adds types in sets of 2
  for (unsigned int i = 0; i < cards.size() / 2; i++) {
    int cardType = random(0, 5);
    cards.at(i).setType(cardType);

    bool placeFound = false;
    while (!placeFound) {
      int newPlace = random(cards.size() / 2, cards.size() - 1);
      if (cards.at(newPlace).getType() == -1) {
        cards.at(newPlace).setType(cardType);
        placeFound = true;
      }
    }
  }
}

void Game::update() {
  // End game
  if (cards.size() == 0) {
    // // Name input
    // if (keypressed()) {
    //   int newkey = readkey();
    //   char ASCII = newkey & 0xff;
    //   char scancode = newkey >> 8;

    //   // a character key was pressed; add it to the string
    //   if (ASCII >= 32 && ASCII <= 126 && edittext.length() < 25 &&
    //       scancode != KEY_SPACE) {
    //     // add the new char
    //     iter = edittext.insert(iter, ASCII);
    //     // increment both the caret and the iterator
    //     iter++;
    //   }
    //   // some other, "special" key was pressed; handle it here
    //   else {
    //     if (scancode == KEY_DEL) {
    //       if (iter != edittext.end()) {
    //         iter = edittext.erase(iter);
    //       }
    //     }
    //     if (scancode == KEY_BACKSPACE) {
    //       if (iter != edittext.begin()) {
    //         iter--;
    //         iter = edittext.erase(iter);
    //       }
    //     }
    //     if (scancode == KEY_RIGHT) {
    //       if (iter != edittext.end()) {
    //         iter++;
    //       }
    //     }
    //     if (scancode == KEY_LEFT) {
    //       if (iter != edittext.begin()) {
    //         iter--;
    //       }
    //     }
    //     if (scancode == KEY_ENTER) {
    //       fade_out(16);
    //       gameScreen = MENU;
    //       addScore(edittext);
    //       draw(false);
    //       fade_in(16);
    //     }
    //   }
    // }
  }
  // Go to menu
  else if (KeyListener::keyPressed[SDL_SCANCODE_M]) {
    setNextState(StateEngine::STATE_MENU);
  }

  // Card logic
  // Count number of flipped cards
  numberSelected = 0;
  for (unsigned int i = 0; i < cards.size(); i++)
    if (cards.at(i).getSelected())
      numberSelected++;

  // Do card logic
  for (unsigned int i = 0; i < cards.size(); i++)
    cards.at(i).logic();

  // Find the placing of the two flipped cards
  if (numberSelected > 0) {
    for (unsigned int i = 0; i < cards.size(); i++) {
      if (cards.at(i).getSelected()) {
        cardSelected1 = i;
        break;
      }
    }
    for (unsigned int i = 0; i < cards.size(); i++) {
      if (cards.at(i).getSelected()) {
        if (cardSelected1 != i) {
          cardSelected2 = i;
          break;
        }
      }
    }
  }

  if (numberSelected == 2 && cards.at(cardSelected1).getAnimationDone() &&
      cards.at(cardSelected2).getAnimationDone() &&
      cards.at(cardSelected1).getSelected() &&
      cards.at(cardSelected2).getSelected()) {
    if (cards.at(cardSelected1).getType() ==
        cards.at(cardSelected2).getType()) {
      cards.at(cardSelected1).match();
      cards.at(cardSelected2).match();
      if (cards.at(cardSelected1).getOffScreen() &&
          cards.at(cardSelected2).getOffScreen()) {
        cards.erase(cards.begin() + cardSelected1);
        cards.erase(cards.begin() + cardSelected2 - 1);
        moves++;
      }
    } else {
      cards.at(cardSelected1).deselect();
      cards.at(cardSelected2).deselect();
      moves++;
    }
  }
}

void Game::draw() {
  // Background
  asw::draw::sprite(background, 0, 0);

  // Show Moves
  asw::draw::primRectFill(15, 15, 200, 70, asw::util::makeColor(255, 255, 255));
  asw::draw::text(font, "Moves:" + std::to_string(moves), 20, 20,
                  asw::util::makeColor(0, 0, 0));

  // Draw cards
  for (unsigned int i = 0; i < cards.size(); i++) {
    cards.at(i).draw();
  }

  if (cards.size() == 0) {
    // // Create gui
    // textprintf_centre_ex(font, 640, 310, asw::util::makeColor(0, 0, 0), -1,
    //                      "Congratulations! Enter Your Name");

    // // Input rectangle
    // asw::draw::primRectFill(400, 408, 892, 452, asw::util::makeColor(0, 0,
    // 0)); asw::draw::primRectFill(402, 410, 890, 450,
    //                         asw::util::makeColor(255, 255, 255));

    // // Output the string to the screen
    // textout_ex(font, edittext.c_str(), 410, 410, asw::util::makeColor(0, 0,
    // 0),
    //            -1);

    // // Draw the caret
    // vline(text_length(font, edittext.c_str()) + 410, 412, 448,
    //       asw::util::makeColor(0, 0, 0));
  }
}

void Game::addScore(const std::string& name) {
  // Update table
  // updateScores(difficulty);

  // Update List
  for (int i = 0; i < 10; i++) {
    if (moves < atoi(scores[i][1].c_str())) {
      for (int t = 9; t > i; t--) {
        scores[t][1] = scores[t - 1][1];
        scores[t][0] = scores[t - 1][0];
      }
      scores[i][1] = convertInt(moves);
      if (name == "") {
        scores[i][0] = "Anonymous";
      } else {
        scores[i][0] = name;
      }

      break;
    }
  }

  // Save Scores
  std::ofstream saveFile;
  // saveFile.open(fileName.c_str());

  for (int i = 0; i < 10; i++) {
    for (int t = 0; t < 2; t++) {
      saveFile << scores[i][t] << " ";
    }
  }
  saveFile.close();
}