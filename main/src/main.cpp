#include <qapplication.h>

#include "Main.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  ui::Main form{};

  form.show();
  return app.exec();
}