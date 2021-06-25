#include "character.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>


int main(int argc, char *argv[]) {
  QCoreApplication qapp(argc, argv);
  QString exe_dir = qapp.applicationDirPath();
  qapp.exit();
  QString root_dir = exe_dir.mid(0, exe_dir.lastIndexOf('/') + 1);
  Character Tina_Aria("Tina_Aria",
                      root_dir + "game_info/character/main_char.json");
  QTextStream out{stdout};
  out << Tina_Aria;
}
