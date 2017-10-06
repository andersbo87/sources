#include "showcountries.h"
#include "ui_showcountries.h"

/**
 * @brief ShowCountries The ShowCountries class constructor
 * @param windowTitle The title to be used with message boxes (QMessageBox)
 * @param pg A pointer to the PostgreSQL database class.
 * @param parent
 */
ShowCountries::ShowCountries(QString windowTitle, psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowCountries)
{
    ui->setupUi(this);
    setFixedSize(size());
    p = pg;
    title = windowTitle;
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()));
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()));
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()));
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()));
    connect(ui->comboBoxLandID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxCountryIDChanged()));
    connect(ui->lineEditCountryName, SIGNAL(textChanged(QString)), this, SLOT(lineEditCountrynameChanged()));
    getCountries();
    getCountry(1);
    countryIDchanged = false;
    changed = false;
}

// Metoder som henter verdier:
/**
 * @brief ShowCountries::getCountryID Gets the ID of the current country
 * @return The identification number to be returned
 */
int ShowCountries::getCountryID()
{
    return countryID;
}

/**
 * @brief ShowCountries::getCountryName Gets the name of the current country
 * @return The name of the country
 */
QString ShowCountries::getCountryName()
{
    return countryName;
}

// Metoder som setter verdier:
/**
 * @brief ShowCountries::setCountryID Sets the current identification number of a country.
 * @param newID The new country ID
 */
void ShowCountries::setCountryID(int newID)
{
    countryID = newID;
}

/**
 * @brief ShowCountries::setCountryName Sets a new name of the current country
 * @param newName The new name of the country
 */
void ShowCountries::setCountryName(QString newName)
{
    countryName = newName;
}

// Andre offentlige metoder:
/**
 * @brief ShowCountries::getCountry Fetches information about the current country and fills the combobox and textbox with the new information.
 * @param countryID The ID of the country in question.
 */
void ShowCountries::getCountry(int countryID)
{
    try
    {
        ui->comboBoxLandID->setCurrentText(QString::number(countryID));
        ui->lineEditCountryName->setText(p->getCountryName(countryID));
        setCountryID(countryID);
        setCountryName(ui->lineEditCountryName->text());
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

/**
 * @brief ShowCountries::getCountries Builds a QLinkedList of integers. This list is then added to the combobox.
 */
void ShowCountries::getCountries()
{
    try
    {
        QLinkedList<int> list = p->fillList("SELECT landid FROM land ORDER BY landid ASC");
        int i;
        for(i = 0; i < list.count(); i++)
        {
            ui->comboBoxLandID->addItem(QString::number(i+1));
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


// Private methods
/**
 * @brief ShowCountries::isChanged Checks if there are unsaved changes in the current record.
 * @return True if ther have been one or more changes and false otherwise.
 */
bool ShowCountries::isChanged()
{
    return changed;
}

/**
 * @brief ShowCountries::setChanged Use this method once a change have been saved to the database or if the user is modifying some data.
 * @param change True if there have been one or more changes and false if the changes have been saved.
 */
void ShowCountries::setChanged(bool change)
{
    changed = change;
}

/**
 * @brief ShowCountries::checkChanges Checks if there are unsaved changes.
 */
void ShowCountries::checkChanges()
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
            if(p->updateCountry(getCountryName(), getCountryID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(title);
                msg2.setText("Landet ble oppdatert og har følgende verdier:\nLandid: " + QString::number(getCountryID()) + "\nLandnavn: " + getCountryName());
                msg2.exec();
            }
        }
        setChanged(false);
    }
}


// Metoder som er definert under "private slots:"
void ShowCountries::buttonFirstClicked()
{
    checkChanges();
    getCountry(1);
    ui->btnFirst->setEnabled(false);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(true);
    ui->btnPrev->setEnabled(true);
}

void ShowCountries::buttonLastClicked()
{
    checkChanges();
    getCountry(lastID);
    ui->btnFirst->setEnabled(true);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPrev->setEnabled(true);
}

void ShowCountries::buttonNextClicked()
{
    checkChanges();
    int currentCountry = getCountryID();
    getCountry(currentCountry +1);
    ui->btnFirst->setEnabled(true);
    ui->btnPrev->setEnabled(true);
    if(currentCountry + 1 == lastID)
    {
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
}

void ShowCountries::buttonPreviousClicked()
{
    checkChanges();
    int currentCountry = getCountryID();
    getCountry(currentCountry -1);
    ui->btnLast->setEnabled(true);
    ui->btnNext->setEnabled(true);
    if(currentCountry - 1 == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
    }
}

void ShowCountries::comboboxCountryIDChanged()
{
    int currID = ui->comboBoxLandID->currentText().toInt();
    checkChanges();
    countryIDchanged = true;
    getCountry(currID);
    countryIDchanged = false;
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

void ShowCountries::lineEditCountrynameChanged()
{
    setCountryName(ui->lineEditCountryName->text());
    if(!countryIDchanged)
        setChanged(true);
}

void ShowCountries::closeEvent(QCloseEvent *event)
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
            if(p->updateCountry(getCountryName(), getCountryID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle(title);
                msg2.setText("Landet ble oppdatert og har følgende verdier:\nLandid: " + QString::number(getCountryID()) + "\nLandnavn: " + getCountryName());
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
ShowCountries::~ShowCountries()
{
    delete ui;
}
