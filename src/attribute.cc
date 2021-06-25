#include "attribute.h"

Attribute::Attribute(QString _type) {
  if (_type == "Physical") {
    type = Attribute_Type::Physical;
  } else if (_type == "Magical") {
    type = Attribute_Type::Magical;
  } else if (_type == "Healing") {
    type = Attribute_Type::Healing;
  } else if (_type == "Null") {
    type = Attribute_Type::Null;
  }
}

Attribute::Attribute(Attribute_Type _type) : type{_type} {}

QString Attribute::get_name() {
  switch (type) {
  case Attribute_Type::Physical:
    return "Physical";
  case Attribute_Type::Magical:
    return "Magical";
  case Attribute_Type::Healing:
    return "Healing";
  case Attribute_Type::Null:
    return "Null";
  default:
    return "";
  }
}

Attribute_Type Attribute::get_type() { return type; }

QString Attribute::get_char_atk() {
  switch (type) {
    switch (type) {
    case Attribute_Type::Physical:
      return "ATK";
    case Attribute_Type::Magical:
      return "MATK";
    case Attribute_Type::Healing:
      return "MDEF";
    default:
      return "";
    }
  }
}

QString Attribute::get_char_def() {
  switch (type) {
  case Attribute_Type::Physical:
    return "DEF";
  case Attribute_Type::Magical:
    return "MDEF";
  default:
    return "";
  }
}
