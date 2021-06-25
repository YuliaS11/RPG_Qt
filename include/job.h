#ifndef JOB_H
#define JOB_H

#include "skill.h"
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

class Character;
class Skill;

union Skill_List {
  vector<Skill *> skills;
  vector<Skill_List> sub_lists;
};

struct Skill_Container {
  vector<Skill_List> list;
  vector<bool> is_list; //
};

struct Ability_Avalible {
  Status *perk; // The perk associated with Ability by adding a persistent
                // status to the owner.
  Skill *move;  // Can alternatively acquire Ability instead of Perk.
  vector<Ability_Avalible *>
      requirement; // Ability required to activate this one
  vector<Ability_Avalible *>
      required;                 // Ability requiring this one to activate.
  unsigned char required_jp;    // Spend JP within a class to unlock.
  unsigned char required_level; // Required level to unlock.
  bool automatic; // Automatically acquired ability once the requirements are
                  // met. This is used for base perks belonging to the job and
};

class Job {
private:
  QString job_name;
  unsigned char max_job_level;
  vector<vector<unsigned short>> stat_modifier;
  vector<Ability_Avalible> avalible_perks;

public:
  Job(QString job_name, QString filename);
  virtual QString get_job_name();
  virtual unsigned char get_max_job_level();
  virtual vector<unsigned short> &get_jp_requirement();
  virtual vector<vector<unsigned short>> &get_stat_modifier();
  virtual vector<Ability_Avalible> &get_avalible_perks();
};

class Char_Job {
protected:
  Job *job; // The job itself
  unsigned char job_level;
  unsigned short job_points;
  unsigned short
      usable_job_points; // Abilities are designed to toggle on and off at will.
                         // Only so much jp as the job max can be used
  vector<bool> perk_active;
  vector<bool> perk_avalible;
  Character *user; // Reference the user of the job, in particular to pass to it
  bool main;       // Job which the character begins with, requiring

public:
  unsigned char get_job_level();
  void add_jp(unsigned short jp);
  unsigned short get_jp();
  unsigned short get_unused_jp();
  bool can_activate_perk(QString perk_name);
  void activate_perk(QString perk_name);
  bool
  deactivate_perk(QString perk_name); // Will deactivate all perk taking
                                      // the current one as requirement. Return
                                      // false if the perk is mandatory
}; // The decription of a job a character is part of

#endif
