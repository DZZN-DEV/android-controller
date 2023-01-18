#include <QApplication>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  app.setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);

  QFile styleSheet(":qdarkstyle/dark/darkstyle.qss");
  if (styleSheet.exists()) {
    styleSheet.open(QFile::ReadOnly | QFile::Text);
    QTextStream ts(&styleSheet);
    app.setStyleSheet(ts.readAll());
  }

  MainWindow mainWindow;
  mainWindow.showFullScreen();
  return app.exec();
}
