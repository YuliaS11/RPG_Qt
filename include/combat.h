#ifndef COMBAT_H
#define COMBAT_H

#include "character.h"

class Controller;
class Faction;
class Status;
class State;
class Skill;
class General_Manager;

class Combat_Entity {
private:
  QString name;
  Character *character;
  unique_ptr<Controller> cont;
  vector<Status_Container> statuses;
  State state;
  unsigned short turn_point; // How far a character in action, primarily used
                             // for Paused TAB
  void get_statuses();       // On Combat Start, pass state and status effect on
                             // character to combat entity.
  void set_statuses(); // On Combat End, pass state and status effect on combat
                       // entity to tracked character like the player's team,
                       // such as poison, unconscious, etc.

public:
  virtual QString get_name();
  Combat_Entity(Character *_character, unsigned short _turn_points = 0);
  friend class Combat_Manager;
};

class Script_Entity;

struct Turn {
  Combat_Entity *ce; // The combat entity of the turn.
  unique_ptr<Action>
      action; // If it's already loaded, then the turn will execute that.
              // If it's not null, the combat controller will decide what to do.
  unsigned char
      inserted_turn; // If such a turn is inserted due to an effect, such as a
                     // counter or a follow up team attack. this also represent
                     // priority when the value is above 1, with followed up
                     // attacks having higher priority than counter
};

enum class Combat_Signal { Combat_Begin, Combat_End };

class Combat_Manager {
public:
protected:
  General_Manager * general_manager;
  unsigned int gold; // The gold rewarded at the end of the battle.
  unsigned int exp;  // The exp rewarded at the end of the battle. EXP
                     // acquisition varies by each character.
  unsigned int jp;   // The jp rewarded at the end of the battle. JP acquisition
                     // varies by each character.
  vector<unique_ptr<Character>> temp_chars;
  // Characters which only persist within the scope of combat
  // manager, typically enemies.
  vector<unique_ptr<Combat_Entity>> entities;
  // A List of combat entities, which are loaded
  // from the general manager or char
  QTextStream announcer;
  vector<Turn> turn_order; // The same Entity can appear multiple times inside
                           // a turn order.

public:
  Combat_Manager(QString filename);
  void pass_turn(); // Pass turn, which if the character
  unsigned int get_gold();
  void set_gold(unsigned int _gold);
  unsigned int get_exp();
  unsigned int get_jp();
  void insert_turn(Character *, Skill *); // Insert the turn to the
  void spawn_entity();
};

#endif
