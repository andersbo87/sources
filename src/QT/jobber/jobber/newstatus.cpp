#include "newstatus.h"
#include "ui_newstatus.h"
#include <QPushButton>

NewStatus::NewStatus(psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewStatus)
{
    p = pg;
    ui->setupUi(this);
    close = false;
    changed = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(OKButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditStatusName, SIGNAL(textChanged(QString)), this, SLOT(lineEditStatusNameChanged()));
}

bool NewStatus::canSave()
{
    if(status.length() == 0)
        close = false;
    else
        close = true;
    return close;
}

void NewStatus::setStatus(QString newStatus)
{
    status = newStatus;
}

QString NewStatus::getStatus()
{
    return status;
}

void NewStatus::closeEvent(QCloseEvent *event)
{
    if(canSave())
    {
        event->ignore();
        if(changed)
        {
            QMessageBox msg;
            msg.setWindowTitle("Jobber");
            msg.setStandardButtons(msg.Yes);
            msg.addButton(msg.Cancel);
            msg.addButton(msg.No);
            msg.setDefaultButton(msg.Yes);
            msg.setText("De siste endringene du gjorde er ikke blitt lagret. Vil du lagre det nå?");
            int res = msg.exec();
            if(res == QMessageBox::Yes)
            {
                if(p->insertStatus(getStatus()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle("Jobber");
                    msg.setIcon(msg.Information);
                    msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
                    msg.exec();
                    event->accept();
                }
                else
                {
                    QMessageBox msg;
                    msg.setIcon(msg.Warning);
                    msg.setWindowTitle("Jobber");
                    msg.setText("Noe har gått galt.");
                    msg.exec();
                }
            }
            else if(res==QMessageBox::No)
            {
                event->accept();
            }
        }
        else
        {
            if(p->insertStatus(getStatus()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle("Jobber");
                msg.setIcon(msg.Information);
                msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
                msg.exec();
                event->accept();
            }
        }
    }
}

void NewStatus::lineEditStatusNameChanged()
{
    setStatus(ui->lineEditStatusName->text());
    changed = true;
}

void NewStatus::OKButtonClicked()
{
    if(canSave())
    {
        if(p->insertStatus(getStatus()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle("Jobber");
            msg.setIcon(msg.Information);
            msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
            msg.exec();
            hide();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle("Jobber");
        msg.setIcon(msg.Warning);
        msg.setText("Alle felt må fylles ut.");
        msg.exec();
    }
}

NewStatus::~NewStatus()
{
    delete ui;
}
