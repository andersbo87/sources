#include "showstatuses.h"
#include "ui_showstatuses.h"

ShowStatuses::ShowStatuses(psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowStatuses)
{
    p = pg;
    ui->setupUi(this);
}

void ShowStatuses::closeEvent(QCloseEvent *event)
{
    event->accept();
}

ShowStatuses::~ShowStatuses()
{
    delete ui;
}
