#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webEngineView->load(QUrl("localhost:5050"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
