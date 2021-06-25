#ifndef STATE_H
#define STATE_H

#include "skill.h"
#include "status.h"
#include <QtCore/QString>
#include <memory>
#include <vector>

using std::vector;

class State {
private:
  QString name;
  State_Type st;
  Skill *skill;
  Character *owner;
  // The stored action which will be unleashed upon a target.
  // When charging, this skill will be unleashed when the remaining
  // turn goes to zero, and reset. When defending, this skill will
  // be the counter skill. When Idling, this skill will be the
  char passed_turns;    // The turns which the state has been active.
  char remaining_turns; // Remaining turn of a state.

public:
  State(Character *_owner, State_Type _st);
  ~State();
  QString get_name();
  State_Type get_state();

  void load_skill(Skill *_skill);
  void turn_end();   // When a character ends a turn
  void turn_start(); // When a character starts a turn
  void status_end();
  void mod_stats();
  void adjust_execution(Action &Action);
  void before_execution(Action &action);
  // Before Execution of a skill by the character
  void during_execution(Action &action);
  // Affect the move during after crit, potency,
  // hit and status hit is determined. Loaded
  // each time the move is affected. This can
  // add extra effect on crit
  void after_execution(Action &action);
  // After Execution of a skill by the character

  void adjust_affected(Action &action);
  void before_affected(Action &action);
  void during_affected(Action &action);
  void after_affected(Action &action);
  // The side getting affected
}; // A character can only have a single state. Generally, this is not meant to
   // be extended beyond the states defined in this file

#endif