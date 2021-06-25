#ifndef GENERAL_H
#define GENERAL_H

#include "attribute.h"
#include "character.h"
#include "combat.h"
#include "job.h"
#include "skill.h"
#include "state.h"
#include "status.h"

using std::map;
using std::unique_ptr;
using std::vector;

enum class Manager_Error {
  No_Error,
  Double_Add, // If a resource already has a name during resource allocation phase
  Invalid_Name // If the name does not exist
};

class General_Manager {
private:
  map<QString, unique_ptr<Skill>> skills;
  map<QString, unique_ptr<Status>> statuses;
  map<QString, unique_ptr<Job>> jobs;
  map<QString, unique_ptr<Character>> tracked_characters;
  // characters which are tracked, and leveled accordingly
  map<QString, unique_ptr<Character>> character_templates;
  // characters which are templated, which copy constructor will be made.
  map<QString, unique_ptr<Element>> elements;
  map<QString, unique_ptr<Enchantment>> enchantments;
  map<QString, unique_ptr<Item>> items;
  map<QString, unique_ptr<Skill>> item_skills;

  unique_ptr<Combat_Manager> Combat_Manager;
  vector<Item> party_items;
  vector<unsigned short> item_stack;
  unsigned int gold;

public:
  void load_resource(); // load resource by files
  Skill *get_skill(QString name);
  Status *get_status(QString name);
  Job *get_job(QString name);
  Character *get_tracked_character(QString name);
  Character *get_template_character(QString name);
  Element *get_element(QString name);
  Enchantment *Enchantment(QString name);
}; // The General Manager exist above all other objects, and owns everything
   // besides GUI

#endif