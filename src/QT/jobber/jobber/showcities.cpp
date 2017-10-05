#include "showcities.h"
#include "ui_showcities.h"

ShowCities::ShowCities(psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowCities)
{
    p = pg;
    ui->setupUi(this);
}

void ShowCities::closeEvent(QCloseEvent *event)
{
    event->accept();
}

ShowCities::~ShowCities()
{
    delete ui;
}
