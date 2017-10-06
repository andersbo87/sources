#include "newcountry.h"
#include "ui_newcountry.h"
#include <QPushButton>

/**
 * @brief NewCountry::NewCountry NewCountry class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class
 * @param parent
 */
NewCountry::NewCountry(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewCountry)
{
    ui->setupUi(this);
    setFixedSize(size());
    title = windowTitle;
    p = pg;
    close = false;
    changed = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(OKButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditCountryName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCountryNameChanged()));
}

// Offentlige metoder som henter verdier:
/**
 * @brief NewCountry::getCountry Gets the current country name.
 * @return The name of the country
 */
QString NewCountry::getCountry()
{
    return country;
}

// Offentlige metoder som setter verdier
/**
 * @brief NewCountry::setCountry Sets the name of the country
 * @param newCountry The new name of the country
 */
void NewCountry::setCountry(QString newCountry)
{
    country = newCountry;
}

// Andre offentlite metoder
NewCountry::~NewCountry()
{
    delete ui;
}

// Private metoder
/**
 * @brief NewCountry::canSave Checks if the unsaved changes can be saved or not.
 * @return True if the changes can be saved (getCountry length is >= 1) and false otherwise.
 */
bool NewCountry::canSave()
{
    if(getCountry().length() == 0)
        close = false;
    else
        close = true;
    return close;
}

/**
 * @brief NewCountry::closeEvent Code to be executed when the window closes
 * @param event This pointer points to the QCloseEvent class that contains functions to prvent the window from closing.
 */
void NewCountry::closeEvent(QCloseEvent *event)
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
                if(p->insertCountry(getCountry()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle(title);
                    msg.setIcon(msg.Information);
                    msg.setText("Det nye landet ble lagret med følgende verdier:\nLandnavn: " + getCountry());
                    msg.exec();
                    event->accept();
                }
            }
            else if(res == QMessageBox::No)
            {
                event->accept();
            }
        }
        else
        {
            if(p->insertCountry(getCountry()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle(title);
                msg.setIcon(msg.Information);
                msg.setText("Det nye landet ble lagret med følgende verdier:\nLandnavn: " + getCountry());
                msg.exec();
                event->accept();
            }
        }
    }
}

// Metoder definert under "private slots":
void NewCountry::lineEditCountryNameChanged()
{
    setCountry(ui->lineEditCountryName->text());
    changed = true;
}

void NewCountry::OKButtonClicked()
{
    if(canSave())
    {
        if(p->insertCountry(getCountry()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle(title);
            msg.setIcon(msg.Information);
            msg.setText("Det nye landet ble lagret med følgende verdier:\nLandnavn: " + getCountry());
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
