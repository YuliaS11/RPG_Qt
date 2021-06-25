#ifndef SKILL_H
#define SKILL_H

#include "attribute.h"
#include <QtCore/QString>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

class Character;
class Status;
class Status_Container;
class State;
class Element;
class Action;

enum class State_Type {
  Defend,
  Idle,
  Knockout,
  Charge,
  Ghost,
  GhostCharge,
  Removed
};
// Defend means defending, with by default reduce physical damage. If a skill is
// loaded, will counter with the skill by adding a new turn.

// Idle means Idling, with nothing being done in particular.

// Knockout means incapacitated, is incapable of being affected by most actions,
// with the character hp at 0.

// Charge means the character is charing an attack with the loaded skill, which
// will unloaded upon completion. Set the loaded skill to null

// Ghost means the character is knockout, but may still perform certain actions.

// GhostCharge means the character is charging a move while being a ghost.

// Removed means no longer part of the battle, true for most defeated enemies.

struct Skill_List {
  vector<vector<Skill *>> skill_list; // List and sublists of skills
};

struct Skill_Cost {
  QString consumed_stats; // Will be "MP", "HP", "HPercent", "MPPercent" or item
                          // name
  short base_cost;
};

struct Inflict_Status {
  Status *status; // Status effect, which will be moved to the
                  // target.(also in terms of unique_ptr)
  bool remove;    // if not empty, will remove status instead
  unsigned char status_probability;
  // The probability of which the status will be inflicted in percentage. If
  // 253, there won't be a hit check. If 254, means it will always lands. If
  // 255, will ignore even immunity. Normally cannot go beyond 252. The move
  // itself must hit first, however.
  int potency;
  // If the status depends on potency
  bool did_inflict;
  int (*get_potency)(Action &_action);
};

struct Potency {
  Attribute attribute;
  vector<Element *> elements;
  int base_potency;
  short multipler;             // Typically Elemental Damage
  unsigned char affected_stat; // 0 for hp, 1 for mp, 2 for hp percentage, 3 for
                               // mp percentage
  unsigned char crit_chance;
  unsigned char crit_multiplier;
  unsigned short random_lower; // 1/10000
  unsigned short random_upper; // 1/10000
  int final_potency;
  bool did_crit;
  int (*get_potency)(Character *_executor, Character *_target);
};

struct Summon_Entity {
  bool opening_move; // If true, summon will use opening move.
  QString entity_name;
  Character
      *summoned; // Construct a character to be summoned. Copy is contructed.
  QString scaled_stat; // The stat the entity scale off of, empty for no scaling
  unsigned char
      lifespan; // How long the entity will be summoned, 0 for
                // opening_move, 253 for tied to summoner or target's status,
                // 254 for until death, 255 for until combat ends.
};

struct Set_State {
  State_Type type;
  Skill *state_skill;
};

struct Affect_Item {
  QString item_name;
  unsigned char effect; // 0 for gain, 1 for lose, 2 for steal, 3 for equip
};

enum class Effect_Type { State, Status, Potency, Item, Summon };

class Effect {
  QString name;
  Effect_Type type;
  union {
    Set_State state;
    Inflict_Status status;
    Potency potency;
    Affect_Item item;
    Summon_Entity summon;
  };
};

class Skill {
public:
  // Predefined keywords, may be expanded. If special damage is not present,
  // then the move will be constructed per usual.
  static const QString ignore_defense; // If the skill ignore target's defense.
  static const QString random_target;
  // If the move picks a wide range of possible targets
  static const QString group_casting;
  // If by default the skill hit an entire faction at once.
  // If both the previous and this toggle is on, then one may
  // switch between single and multi casting.
  static const QString select_random; // Select random targets, require previous
                                      // keyword to function.
  static const QString multi_reduction; // If hitting multiple targets causes
                                        // reduction in potency.
  static const QString counter_stealth;
  // With the keyword, the skill cannot be countered
  static const QString can_reflect;
  // If the move is reflected by a reflect
  // status if the attribute of the barrier matches
  static const QString special_damage;
  // If the move does not follow the regular damage method
  // so statuses does not affect its potency meant for
  // regular attacks.
  static const QString target_unconcious;
  // If the move can target a knocked-out
  // target, such as revive. Automatic target selection
  // will always target unconcious entities that can be
  // revived.
  static const QString ghost_skill;
  // This move can be used by ghosts
  static const QString item_skill;
  // This move consumes items and will be boosted accordingly.

protected:
  QString name;
  vector<QString> effect_names;
  vector<Effect *> effects; // List of Effects.
  Skill_Cost cost;

  Action (*make_action_pointer)(Skill *_this, Character *owner,
                                vector<Character *> &targets,
                                Character *intended_target);
  // factory method to produce an action based on skill. If set to null, will
  // use the default below
  static Action make_action_default(Skill *_this, Character *owner,
                                    vector<Character *> &targets,
                                    Character *intended_target);

  void (*reload_action_pointer)(Skill *_this, Action &action);
  // reload action when targets have changed, but otherwise. If set to null,
  // will use default below
  static void
  reaload_action_default(Skill *_this,
                         Action &action); // reload action when targets

public:
  Skill(QString filename);
  Action make_action(Character *owner, vector<Character *> &targets,
                     Character *intended_target);
  void reload_action(Action &action);
  // factory method to produce an action based on skill
  friend class Action_Step;
  friend class Action;
};

struct Action {
  Character *owner;
  vector<Character *> avalible_targets;
  Character
      *intended_target; // The currently tracked target for single target moves
  vector<QString> keywords;
  vector<Effect>
      steps; // Action Steps which steps gets executed at once. Within the same
             // cycle targets cannot be performed on twice.
  vector<Effect> past_steps; // Actions steps which are already executed
  Skill *base_skill;
  vector<QString> keywords;
  State set_state;
  Skill_Cost final_cost;
  void reload_target(); // Reloads target when the existing target becomes
                        // knocked out or otherwise incapable of being affected.
};

#endif
