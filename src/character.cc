#include "character.h"
#include "text_color.h"
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>

const unsigned char Character::stat_count = 9;
const vector<QString> Character::stat_names = {
    "HP", "MP", "ATK", "DEF", "MATK", "MDEF", "SPD", "LV", "EXP"};

Character::Character(const QString charname, const QString filename) {
  base_stats.reserve(stat_count);
  real_stats.reserve(stat_count);
  QFile qf(filename);
  if (!qf.open(QIODevice::ReadOnly)) {
    qWarning() << "File " << filename << " does not exist, or is not readable."
               << Qt::endl;
    qf.close();
    throw Char_Exception::JsonReadFail;
  }
  QString qjs = qf.readAll();
  qf.close();
  QJsonDocument qjd = QJsonDocument::fromJson(qjs.toUtf8());
  QJsonObject qja = qjd.object().value(charname).toObject();
  first_name = qja.value("first_name").toString();
  last_name = qja.value("last_name").toString();
  unsigned int val;
  foreach (QString qs, stat_names) {
    val = qja.value(qs).toInt();
    base_stats.emplace_back(val);
    real_stats.emplace_back(val);
    if (qs == "HP" || qs == "MP")
      mutable_stats.emplace_back(val);
  }
}

QTextStream &operator<<(QTextStream &out, const Character &c) {
  out.setCodec("UTF-8");
  out << c.first_name << ' ' << c.last_name << ':' << Qt::endl;
  for (unsigned char i = 0; i < Character::stat_count; i++) {
    out << c.stat_names[i] << ": " << c.base_stats[i] << ' ' << YELLOW
        << QChar(0x2192) << RESET << ' ' << c.real_stats[i] << ' ';
    if (c.real_stats[i] > c.base_stats[i]) {
      out << GREEN << QChar(0x25B2) << ' ' << c.real_stats[i] - c.base_stats[i];
    }
    if (c.real_stats[i] < c.base_stats[i]) {
      out << RED << QChar(0x25BC) << ' ' << c.base_stats[i] - c.real_stats[i];
    }
    out << RESET << Qt::endl;
  }
  return out;
}
