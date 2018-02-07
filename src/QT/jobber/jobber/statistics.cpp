#include "statistics.h"
#include "ui_statistics.h"

/**
 * @brief statistics::statistics statisitcs class constructor.
 * @param pg The pointer to the psql class
 * @param parent Pointer the the parent class
 */
statistics::statistics(psql *pg,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistics)
{
    p = pg;
    ui->setupUi(this);
    updateData();
    connect(ui->btnUpdate, SIGNAL(clicked(bool)), this, SLOT(btnUpdateClicked()));
}

/**
 * @brief statistics::updateData Fetches new application statistics from the database.
 */
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
