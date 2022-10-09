#include "State.h"

#include <iostream>

#include "Game.h"
#include "HighScores.h"
#include "Init.h"
#include "Intro.h"
#include "LevelSelect.h"
#include "Menu.h"

/*****************
 * STATE ENGINE
 *****************/

// Init
StateEngine::StateEngine()
    : nextState(StateEngine::STATE_NULL),
      currentState(StateEngine::STATE_NULL),
      state(nullptr) {}

// Draw
void StateEngine::draw() {
  if (state) {
    // Clear screen
    SDL_RenderClear(asw::display::renderer);

    state->draw();

    // Update screen
    SDL_RenderPresent(asw::display::renderer);
  }
}

// Update
void StateEngine::update() {
  if (state) {
    state->update();
  }

  changeState();
}

// Set next state
void StateEngine::setNextState(const int newState) {
  nextState = newState;
}

// Get state id
int StateEngine::getStateId() const {
  return currentState;
}

// Change game screen
void StateEngine::changeState() {
  // If the state needs to be changed
  if (nextState == STATE_NULL) {
    return;
  }

  // Delete the current state
  if (state) {
    state->cleanup();
    state = nullptr;
  }

  // Change the state
  switch (nextState) {
    case STATE_GAME:
      state = std::make_unique<Game>(*this);
      std::cout << ("Switched state to game.\n");
      break;

    case STATE_MENU:
      state = std::make_unique<Menu>(*this);
      std::cout << ("Switched state to main menu.\n");
      break;

    case STATE_INIT:
      state = std::make_unique<Init>(*this);
      std::cout << ("Switched state to init.\n");
      break;

    case STATE_INTRO:
      state = std::make_unique<Intro>(*this);
      std::cout << ("Switched state to intro.\n");
      break;

    case STATE_HIGH_SCORES:
      state = std::make_unique<HighScores>(*this);
      std::cout << ("Switched state to high scores.\n");
      break;

    case STATE_LEVEL_SELECT:
      state = std::make_unique<LevelSelect>(*this);
      std::cout << ("Switched state to level select.\n");
      break;

    default:
      std::cout << ("Exiting program.");
      break;
  }

  state->init();

  // Change the current state ID
  currentState = nextState;

  // NULL the next state ID
  nextState = STATE_NULL;
}

/*********
 * STATE
 *********/

// Change state
void State::setNextState(const int state) {
  this->engine.setNextState(state);
}
