#ifndef CHARACTER_H
#define CHARACTER_H

#include "attribute.h"
#include "item.h"
#include "job.h"
#include "skill.h"
#include "state.h"
#include "status.h"

#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <memory>
#include <vector>
#include <map>

using std::map;
using std::vector;

class Job;       // A basic job system which is meant to be switched around.
class Skill;     // Anything as basic as attacking or defending.
class Perk;      // Perks, affect how a character behaves or affect their stats.
class Faction;   // Faction system which will also affect quest
class Item;      // Item, such as potions.
class Equipment; // Equipment, which can change stat, attack types, amongst
                 // other things. Also a subclass of Item
class Element;   // Element such as fire, ice, etc.

class Combat_Entity;   // Manage battle such as turn order amongst other things
class General_Manager; // Manage items, character order, jobs, etc.

enum class Char_Exception { JsonReadFail, JsonWriteFail };

enum Stats {
  HP = 0,
  MP = 1,
  ATK = 2,
  DEF = 3,
  MATK = 4,
  MDEF = 5,
  SPD = 6,
  LV = 7,
  EXP = 8
}; // Index for actual stats

class Character {
public:
  static const unsigned char stat_count;
  static const vector<QString> stat_names;

protected:
  QString default_name, first_name, last_name;
  vector<int> base_stats; // The base stats
  vector<int>
      real_stats; // The actual stats, after calculation regarding jobs, perks,
  // equipments, etc, can change during battle.
  vector<int> mutable_stats; // HP, MP, etc.
  vector<Resistance> resists;
  vector<Skill *> moves;
  vector<Faction *> factions;
  vector<Item *> drops;
  vector<Equipment_Container> equips;
  vector<Job *> jobs;
  vector<Status_Container> statuses;
  vector<Status *> immunity;
  bool tracked; // If a character is tracked, for example the main characters,
                // they would get loaded from the save.
  State state;

public:
  Character(const QString templatefile);
  // Load from template
  Character(const QString name, const QString savefile);
  // Load tracked Characters from savefile
  void save_to_file();
  // Save tracked characters.
  void relevel(int _lv);
  // reset the character based on new level.
  virtual ~Character() {}
  General_Manager
      *manager; // Used for loading resources from the general manager
  friend class Combat_Entity;
  friend class General_Manager;
  friend QTextStream &operator<<(QTextStream &out, const Character &c);
  /*virtual void add_perk(Perk *);
  virtual void remove_perk(QString perk_name);*/
  virtual void add_skill(Skill *);
  virtual void remove_skill(QString move_name);
};

QTextStream &operator<<(QTextStream &out, const Character &c);

#endif
