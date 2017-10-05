/**
  @file newcity.cpp
  */
#include "newcity.h"
#include "ui_newcity.h"
#include <QPushButton>
NewCity::NewCity(psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewCity)
{
    p = pg;
    close = false;
    changed = false;
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Lagre");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(OKButtonClicked()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(close()));
    connect(ui->lineEditCityName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCityNameChanged()));
    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(countryIDchanged()));
    getCountryIDs();
}

// Destruktør
NewCity::~NewCity()
{
    delete ui;
}

void NewCity::getCountryIDs()
{
    try
    {
        QLinkedList<int> list;
        list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBox->addItem(QString::number(i+1));
            i++;
        }
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle("Jobber");
        msg.setText(e.what());
        msg.exec();
    }
}

void NewCity::setCountryID(int newCountryID)
{
    countryID = newCountryID;
}

void NewCity::countryIDchanged()
{
    setCountryID(ui->comboBox->currentText().toInt());
    ui->labelCountryName->setText(p->getCountryName(getCountryID()));
    changed = true;
}

QString NewCity::getCityName()
{
    return cityName;
}

void NewCity::setCityName(QString name)
{
    cityName = name;
}

void NewCity::lineEditCityNameChanged()
{
    setCityName(ui->lineEditCityName->text());
    changed = true;
}

bool NewCity::canSave()
{
    if(cityName.length() == 0)
        close = false;
    else
        close = true;
    return close;
}

void NewCity::OKButtonClicked()
{
    if(canSave())
    {
        // Lagrer dataen i databasen.
        if(p->insertCity(getCityName(), getCountryID()))
        {
            // Lukker vinduet.
            QMessageBox msg;
            msg.setWindowTitle("Jobber");
            msg.setIcon(msg.Information);
            msg.setText("Det nye stedet ble lagt inn med følgende data:\nStedsnavn: " + getCityName() + "\nLandid: " + QString::number((getCountryID())));
            msg.exec();
            changed = false;
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

int NewCity::getCountryID()
{
    return countryID;
}

void NewCity::closeEvent(QCloseEvent *event)
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
                if(p->insertCity(getCityName(), getCountryID()))
                {
                    // Lukker vinduet.
                    QMessageBox msg;
                    msg.setWindowTitle("Jobber");
                    msg.setIcon(msg.Information);
                    msg.setText("Det nye stedet ble lagt inn med følgende data:\nStedsnavn: " + getCityName() + "\nLandid: " + QString::number((getCountryID())));
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
            if(p->insertCity(getCityName(), getCountryID()))
            {
                // Lukker vinduet.
                QMessageBox msg;
                msg.setWindowTitle("Jobber");
                msg.setIcon(msg.Information);
                msg.setText("Det nye stedet ble lagt inn med følgende data:\nStedsnavn: " + getCityName() + "\nLandid: " + QString::number((getCountryID())));
                msg.exec();
                event->accept();
            }
        }
    }
}
