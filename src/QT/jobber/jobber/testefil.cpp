#include "testefil.h"
#include "ui_testefil.h"

testefil::testefil(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testefil)
{
    ui->setupUi(this);
}

testefil::~testefil()
{
    delete ui;
}
