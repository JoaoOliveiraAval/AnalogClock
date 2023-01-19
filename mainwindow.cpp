#include "mainwindow.h"

#include "analogclock.h"
#include "qdatetime.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Analog Clock"));
    resize(500, 500);
    AnalogClock *clock = new AnalogClock(this);
    clock->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
