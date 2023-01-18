#include "mainwindow.h"

#include "mainwidget.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  MainWidget* mainWidget = new MainWidget(this);
  setCentralWidget(mainWidget);
}
