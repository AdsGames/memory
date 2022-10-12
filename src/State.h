/**
 * State for machine and State Engine
 * Allan Legemaate
 * 30/12/2016
 * Compartmentalize program into states
 *   which can handle only their own logic,
 *   drawing and transitions
 */

#ifndef STATE_H
#define STATE_H

#include <asw/asw.h>
#include <memory>

// Class
class State;

/*****************
 * STATE ENGINE
 *****************/
class StateEngine {
 public:
  // Init
  StateEngine();

  // Update
  void update();

  // Draw
  void draw();

  // Set next state
  void setNextState(const int state);

  // Get state id
  int getStateId() const;

  // Game states
  enum ProgramState {
    STATE_NULL,
    STATE_INIT,
    STATE_INTRO,
    STATE_MENU,
    STATE_HIGH_SCORES,
    STATE_LEVEL_SELECT,
    STATE_GAME,
    STATE_EXIT,
  };

 private:
  // Change state
  void changeState();

  // Next state
  int nextState = STATE_NULL;

  // State id
  int currentState = STATE_NULL;

  // Stores states
  std::unique_ptr<State> state;
};

/*********
 * STATE
 *********/
class State {
 public:
  // Constructor
  explicit State(StateEngine& engine) : engine(engine){};

  virtual ~State() = default;

  // Init the state
  virtual void init() = 0;

  // Draw to screen
  virtual void draw() = 0;

  // Cleanup
  virtual void cleanup() = 0;

  // Update logic
  virtual void update() = 0;

  // Change state
  void setNextState(const int state);

 private:
  StateEngine& engine;
};

#endif  // STATE_H
