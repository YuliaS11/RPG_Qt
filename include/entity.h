#ifndef ENTITY_H
#define ENTITY_H

#include <QtCore/QString>

class Entity {
protected:
  QString name;

public:
  virtual QString get_name() { return name; }
  virtual ~Entity();

}; // An abstract class which can be a combat entity, a battle announcer or a
   // script manager

class Combat_Entity; // Container of turn based combat entities.

class Announcer_Entity; // Announce Damage, Effect, Crit, amongst other things.
                        // Loosely follow the Observer Design Pattern.

class Script_Entity; // Scripted Battle Entity, different from AI.

#endif
