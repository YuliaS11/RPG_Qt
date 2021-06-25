#ifndef STATUS_H
#define STATUS_H

#include "attribute.h"
#include "skill.h"
#include <QtCore/QString>
#include <memory>

class Character;
class State;

class Status {
public:
  static const QString stackable;
  // if the stat is stackable. The stacking is linear for status.
  static const QString use_potency; // if the status relies on potency.
  static const QString multi_instance;
  // if the status can have multiple instance of the same
  // effect and thus cannot be stackable
  static const QString buff; // if the status is considerd a buff
  static const QString affliction;
  // if the status is considered an affliction for the sake of
  static const QString clearable; // if certain skill can clear it
  static const QString invisible;
  // if the ui is informed of its existence
  static const QString active_inserted_turn;
  // if the status is active on inserted lesser turns. Does not affect
  static const QString linked_to_character;
  // if the status involves another character, such as a cover against attack.

protected:
  QString name;
  unsigned char default_turns; // Cannot exceed 252. 253 for 254 for
                               // persistant, 255 for persistant beyond knockout
  vector<short> stats_mult;
  // multiplier of stat, deviating from 1, compute by 1/100.
  vector<Resistance> resistance_mult;
  vector<QString> keywords;
  vector<Status *>
      mutually_exclusives; // Overrides the given statuses. Cannot include self.
  vector<Status *> immune_to; // Prevents the statuses from being gained.

public:
  Status(const QString filename);

  virtual void turn_end(Status_Container &container) = 0;
  // When a character passes a turn
  virtual void turn_start(Status_Container &container) = 0;
  // When a character starts a turn
  virtual void status_end(Status_Container &container) = 0;
  // When a status runs out. Note that this can happen at the end of battle,
  // and can modify things such as drop chance.
  virtual void mod_stats(Status_Container &container) = 0;
  // Modify when the status runs out of stacks or ends.
  virtual void mod_costs(Skill_Cost &cost, Status_Container &container) = 0;
  // Modify the cost of a skill,
  // primarily for projected damage
  virtual void on_receive(Status_Container &container);

  virtual void adjust_execution(Character *owner,
                                Status_Container &container) = 0;
  // Affect modifiers of the move such as keywords and
  // the number of execution. Only loaded once per move
  virtual void before_execution(Character *owner,
                                Status_Container &container) = 0;
  // Before Execution of a skill by the character
  virtual void during_execution(Character *owner,
                                Status_Container &container) = 0;
  // Affect the move during after crit, potency,
  // hit and status hit is determined. Loaded
  // each time the move is affected. This can
  // add extra effect on crit
  virtual void after_execution(Character *owner,
                               Status_Container &container) = 0;
  // After Execution of a skill by the character

  virtual void adjust_execution(Character *owner,
                                Status_Container &container) = 0;
  // Only loaded once per move
  virtual void before_affected(Character *owner,
                               Status_Container &container) = 0;
  virtual void during_affected(Character *owner,
                               Status_Container &container) = 0;
  virtual void after_affected(Character *owner,
                              Status_Container &container) = 0;
  // The affected side of the move by the target.

  Status_Container make_status(Character *owner, char _active_turns = 0,
                               char stacks = 1, int potency = 0);
  friend struct Status_Container;
  friend class Combat_Manager;
  friend class General_Manager;
};

struct Status_Container {
  Status *base_status;
  Character *owner;  // The character with the status
  char active_turns; // remaining turns.
  char stacks;       // The number of stacks the status is gained.
  int potency;       // If the status has a potency, such as a move that would
                     // strike a target when the target's turn is active.
};

#endif
