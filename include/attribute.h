#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QtCore/QString>
#include <memory>

class Status;

enum class Attribute_Type {
  Physical,
  Magical,
  Healing,
  Null
}; // If the damage is physical such as a weapon, magical such as a spell, or
   // considered as neither. This interaction goes beyond damage calculation

class Attribute {
private:
  Attribute_Type type;

public:
  QString get_name();
  Attribute_Type get_type();
  QString get_char_atk(); // Characteristic Attack Stats
  QString get_char_def(); // Characteristic Defense Stats

  Attribute(QString _type);
  Attribute(Attribute_Type _type);
};

struct Element {
  QString name;
  QString char_status_name;
  Status *char_status;
  QString char_damage;
  Element(QString filename);
};

struct Resistance {
  Element *element;
  short resist; // below 0 for vulenerable, 1-99 for resist, 100 for ignore and
                // above 100 for absorb as hp
  bool absorb_as_mp; // When above 100 and absorb is true, regenerate target's mp instead as 5% of the damage.
  Resistance operator+(Resistance const &other);
  Resistance(Element *_element, short resist, bool absorb_as_mp = false);
};

#endif