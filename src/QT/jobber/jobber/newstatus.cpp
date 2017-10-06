#include "newstatus.h"
#include "ui_newstatus.h"
#include <QPushButton>

/**
 * @brief NewStatus NewStatus class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class
 * @param parent
 */
NewStatus::NewStatus(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewStatus)
{
    p = pg;
    ui->setupUi(this);
    title = windowTitle;
    setFixedSize(size());
    close = false;
    changed = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(OKButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditStatusName, SIGNAL(textChanged(QString)), this, SLOT(lineEditStatusNameChanged()));
}

/**
 * @brief NewStatus::canSave Checks if the changes can be saved
 * @return True if the changes can be saved and false otherwise.
 */
bool NewStatus::canSave()
{
    if(status.length() == 0)
        close = false;
    else
        close = true;
    return close;
}

/**
 * @brief NewStatus::setStatus Sets the new status name
 * @param newStatus the name of the new status
 */
void NewStatus::setStatus(QString newStatus)
{
    status = newStatus;
}
/**
 * @brief NewStatus::getStatus Gets the current status name
 * @return The status name to be returned.
 */
QString NewStatus::getStatus()
{
    return status;
}

/**
 * @brief closeEvent Code to be executed when the window closes
 * @param event This pointer points to the QCloseEvent class that contains functions to prvent the window from closing.
 */
void NewStatus::closeEvent(QCloseEvent *event)
{
    if(canSave())
    {
        event->ignore();
        if(changed)
        {
            QMessageBox msg;
            msg.setWindowTitle(title);
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
                    msg.setWindowTitle(title);
                    msg.setIcon(msg.Information);
                    msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
                    msg.exec();
                    event->accept();
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
                msg.setWindowTitle(title);
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
            msg.setWindowTitle(title);
            msg.setIcon(msg.Information);
            msg.setText("Den nye statuse ble lagt inn med følgende data:\nStatus: " + getStatus());
            msg.exec();
            hide();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setWindowTitle(title);
        msg.setIcon(msg.Warning);
        msg.setText("Alle felt må fylles ut.");
        msg.exec();
    }
}

NewStatus::~NewStatus()
{
    delete ui;
}
