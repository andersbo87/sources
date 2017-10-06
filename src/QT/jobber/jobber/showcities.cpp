#include "showcities.h"
#include "ui_showcities.h"

ShowCities::ShowCities(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowCities)
{
    title = windowTitle;
    p = pg;
    ui->setupUi(this);
    setFixedSize(size());
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()));
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()));
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()));
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()));
    connect(ui->comboBoxCityID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCityIDChanged()));
    connect(ui->comboBoxCountryID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCountryIDChanged()));
    connect(ui->lineEditCityName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCityNameChanged()));
    getCities();
    getCountryIDs();
    getCity(1);
    cityIDchanged = false;
    changed = false;
}

int ShowCities::getCityID()
{
    return cityID;
}

QString ShowCities::getCountryName()
{
    return countryName;
}

int ShowCities::getCountryID()
{
    return countryID;
}

// Metoder som angir nye verdier:
void ShowCities::setCityID(int newID)
{
    cityID = newID;
}

void ShowCities::setCityName(QString newName)
{
    cityName = newName;
}

void ShowCities::setCountryID(int newID)
{
    countryID = newID;
}

void ShowCities::getCity(int cityID)
{
    try
    {
        ui->comboBoxCityID->setCurrentText(QString::number(cityID));
        ui->lineEditCityName->setText(p->getCityName(cityID));
        ui->comboBoxCountryID->setCurrentText(QString::number(p->getCountryID(cityID)));
        setCityID(cityID);
        setCountryID(ui->comboBoxCountryID->currentText().toInt());
        setCityName(ui->lineEditCityName->text());
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(title);
        msg.setText(e.what());
        msg.exec();
    }
}

void ShowCities::getCountryIDs()
{
    try
    {
        QLinkedList<int> list;
        list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        for(int i=0; i < list.count(); i++)
        {
            ui->comboBoxCountryID->addItem(QString::number(i+1));
        }
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(title);
        msg.setText(e.what());
        msg.exec();
    }
}

void ShowCities::getCities()
{
    try
    {
        QLinkedList<int> list = p->fillList("SELECT stedid FROM sted ORDER BY stedid ASC");
        int i;
        for(i= 0; i < list.count(); i++)
        {
            ui->comboBoxCityID->addItem(QString::number(i+1));
        }
        lastID = i;
    }
    catch(std::exception &e)
    {
        QMessageBox msg;
        msg.setIcon(msg.Warning);
        msg.setWindowTitle(title);
        msg.setText(e.what());
        msg.exec();
    }
}

bool ShowCities::isChanged()
{
    return changed;
}

void ShowCities::setChanged(bool change)
{
    changed = change;
}

QString ShowCities::getCityName()
{
    return cityName;
}

void ShowCities::checkChanges()
{
    if(isChanged())
    {
        // Spør om endringer skal lagres.
        QMessageBox msg;
        msg.setWindowTitle(title);
        msg.setIcon(msg.Question);
        msg.setStandardButtons(msg.Yes);
        msg.addButton(msg.No);
        msg.setDefaultButton(msg.Yes);
        msg.setText("Du har gjort noen endringer. Vil du lagre disse?");
        if(msg.exec() == QMessageBox::Yes)
        {
            // Oppdaterer endringene i databasen.
            if(p->updateCity(getCityName(),getCountryID(),getCityID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(title);
                msg2.setText("Stedet ble oppdatert og har følgende verdier:\nStedid: " + QString::number(getCityID()) + "\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
                msg2.exec();
            }
        }
        setChanged(false);
    }
}

void ShowCities::buttonFirstClicked()
{
    checkChanges();
    getCity(1);
    ui->btnFirst->setEnabled(false);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(true);
    ui->btnPrev->setEnabled(true);
}

void ShowCities::buttonLastClicked()
{
    checkChanges();
    getCity(lastID);
    ui->btnFirst->setEnabled(true);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPrev->setEnabled(true);
}

void ShowCities::buttonNextClicked()
{
    checkChanges();
    int currentCity = getCityID();
    getCity(currentCity +1);
    ui->btnFirst->setEnabled(true);
    ui->btnPrev->setEnabled(true);
    if(currentCity + 1 == lastID)
    {
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
}

void ShowCities::buttonPreviousClicked()
{
    checkChanges();
    int currentCity = getCityID();
    getCity(currentCity -1);
    ui->btnLast->setEnabled(true);
    ui->btnNext->setEnabled(true);
    if(currentCity - 1 == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
    }
}

void ShowCities::lineEditCityNameChanged()
{
    setCityName(ui->lineEditCityName->text());
    if(!cityIDchanged)
        setChanged(true);
}

void ShowCities::comboboxCityIDChanged()
{
    int currID = ui->comboBoxCityID->currentText().toInt();
    checkChanges();
    cityIDchanged = true;
    getCity(currID);
    cityIDchanged = false;
    if(currID == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        ui->btnPrev->setEnabled(false);

    }
    else if(currID == lastID)
    {
        ui->btnFirst->setEnabled(true);
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
        ui->btnPrev->setEnabled(true);
    }
    else
    {
        ui->btnFirst->setEnabled(true);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
        ui->btnPrev->setEnabled(true);
    }
}

void ShowCities::comboboxCountryIDChanged()
{
    setCountryID(ui->comboBoxCountryID->currentText().toInt());
    ui->labelCountryName->setText(p->getCountryName(getCountryID()));
    if(!cityIDchanged)
        setChanged(true);
}

void ShowCities::closeEvent(QCloseEvent *event)
{
    if(isChanged())
    {
        event->ignore();
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
            // Oppdaterer endringene i databasen.
            if(p->updateCity(getCityName(),getCountryID(),getCityID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(title);
                msg2.setText("Stedet ble oppdatert og har følgende verdier:\nStedid: " + QString::number(getCityID()) + "\nStedsnavn: " + getCityName() + "\nLandID: " + QString::number(getCountryID()));
                msg2.exec();
            }
            event->accept();
        }
        else if(res == QMessageBox::No)
        {
            event->accept();
        }
    }
}

ShowCities::~ShowCities()
{
    delete ui;
}
