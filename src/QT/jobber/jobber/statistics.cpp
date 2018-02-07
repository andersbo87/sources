#include "statistics.h"
#include "ui_statistics.h"

statistics::statistics(psql *pg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    p = pg;
    ui->setupUi(this);
    updateData();
    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(btnUpdateClicked()));
}

void statistics::updateData()
{
    ui->labelTotalValue->setText(QString::number(p->countTotalApplications()));
    ui->labelAcceptedValue->setText(QString::number(p->countAccepted()));
    ui->labelDeclinedValue->setText(QString::number(p->countDeclinedApplications()));
    ui->labelInterviewValue->setText(QString::number(p->countInterviews()));
    ui->labelRegisteredValue->setText(QString::number(p->countRegisteredApplications()));
    ui->labelSentValue->setText(QString::number(p->countSentApplications()));
    ui->labelWrittenButNotSentValue->setText(QString::number(p->countWrittenButNotSent()));
}

void statistics::btnUpdateClicked()
{
    updateData();
}

statistics::~statistics()
{
    delete ui;
}
