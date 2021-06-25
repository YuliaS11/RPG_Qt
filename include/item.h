#ifndef ITEM_H
#define ITEM_H

#include "attribute.h"
#include "status.h"
#include <QtCore/QString>
#include <vector>

using std::vector;
class Effect;

class Item {
protected:
  unsigned short max_stack;
  unsigned int price;
  QString name;
};

class Consumable : public Item {
  Effect *effect;
  Effect *mixed_effect;
};

class Equipment : public Item {
protected:
  vector<int> strcat_s;
  QString slot;
  bool is_weapon;
  // Only weapon Attributes and Elements are counted.
  Attribute attribute;
  vector<Enchantment *> enchantments;
};

enum class Enchantment_Type { Element, Skill, Status, Resistance };

class Enchantment {
  QString name;
  QString associated_name;
  Enchantment_Type type;
  union {
    Element *elements;
    Skill *item_skill; // When an attack is used, the skill is executed instead of the standard attack.
    Status *added_perks;
    Resistance resist;
  };
};

class Equipment_Container {
  Equipment *base;
  vector<Enchantment> addtional_enchantments;
};

#endif