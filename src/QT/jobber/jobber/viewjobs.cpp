#include "viewjobs.h"
#include "ui_viewjobs.h"

ViewJobs::ViewJobs(psql *pg, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewJobs)
{
    ui->setupUi(this);
    setFixedSize(size());
    p = pg;
    changed = false;
    soknadIDChanged = false;
    getApplications();
    getCityIDs();
    getStatusIDs();
    getApplication(1);
    connect(ui->comboBoxApplicationID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboboxApplicationIDChanged()));
    connect(ui->lineEditTitle, SIGNAL(textChanged(QString)), this, SLOT(lineEditTitleChanged()));
    connect(ui->lineEditCompany, SIGNAL(textChanged(QString)), this, SLOT(lineEditCompanyChanged()));
    connect(ui->comboBoxTownID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxCityIDChanged()));
    connect(ui->comboBoxStatusID, SIGNAL(currentTextChanged(QString)), this, SLOT(comboBoxStatusIDChanged()));
    connect(ui->lineEditDeadline, SIGNAL(textChanged(QString)), this, SLOT(lineEditDealineChanged()));
    connect(ui->btnFirst, SIGNAL(clicked(bool)), this, SLOT(buttonFirstClicked()));
    connect(ui->btnLast, SIGNAL(clicked(bool)), this, SLOT(buttonLastClicked()));
    connect(ui->btnNext, SIGNAL(clicked(bool)), this, SLOT(buttonNextClicked()));
    connect(ui->btnPrev, SIGNAL(clicked(bool)), this, SLOT(buttonPreviousClicked()));
}

ViewJobs::~ViewJobs()
{
    delete ui;
}

/**
 * @brief ViewJobs::isChanged Checks if there have been any unsaved changes to the current record
 * @return True if there are unsaved changes and false otherwise.
 */
bool ViewJobs::isChanged()
{
    return changed;
}

/**
 * @brief ViewJobs::setChanged Sets the changed variable to true if there are unsaved changes, and false if those changes have been saved.
 * @param change true if a record has been changed and false if that record has been saved
 */
void ViewJobs::setChanged(bool change)
{
    changed = change;
}

void ViewJobs::comboBoxStatusIDChanged()
{
    setStatusID(ui->comboBoxStatusID->currentText().toInt());
    ui->labelStatus->setText(p->getStatusName(getStatusID()));
    if(!soknadIDChanged)
        setChanged(true);
}

void ViewJobs::comboBoxCityIDChanged()
{
    setCityID(ui->comboBoxTownID->currentText().toInt());
    ui->labelSted->setText(p->getCityName(getCityID()));
    if(!soknadIDChanged)
        setChanged(true);
}

void ViewJobs::lineEditDealineChanged()
{
    setDate(ui->lineEditDeadline->text());
    if(!soknadIDChanged)
        setChanged(true);
}

void ViewJobs::lineEditCompanyChanged()
{
    setCompany(ui->lineEditCompany->text());
    if(!soknadIDChanged)
        setChanged(true);
}

void ViewJobs::lineEditTitleChanged()
{
    setTitle(ui->lineEditTitle->text());
    if(!soknadIDChanged)
        setChanged(true);
}

/**
 * @brief ViewJobs::closeEvent Code to be executed when the user has ordered the window to be closed.
 * @param event No help available, sorry
 */
void ViewJobs::closeEvent(QCloseEvent *event)
{
    if(isChanged())
    {
        event->ignore();
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
            if(p->updateApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getApplicationID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle("Jobber");
                msg2.setText("Oppdateringen ble lagret med følgende verdier:\nID: " + QString::number(getApplicationID()) + "\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusid: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate());
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

void ViewJobs::checkChanges()
{
    if(isChanged())
    {
        // Spør om endringer skal lagres.
        QMessageBox msg;
        msg.setWindowTitle("Jobber");
        msg.setIcon(msg.Question);
        msg.setStandardButtons(msg.Yes);
        msg.addButton(msg.No);
        msg.setDefaultButton(msg.Yes);
        msg.setText("Du har gjort noen endringer. Vil du lagre disse?");
        if(msg.exec() == QMessageBox::Yes)
        {
            if(p->updateApplication(getTitle(), getCompany(), getCityID(), getStatusID(), getDate(), getApplicationID()))
            {
                QMessageBox msg2;
                msg2.setIcon(msg2.Information);
                msg2.setWindowTitle("Jobber");
                msg2.setText("Oppdateringen ble lagret med følgende verdier:\nID: " + QString::number(getApplicationID()) + "\nTittel: " + getTitle() + "\nBedrift: " + getCompany() + "\nStedid: " + QString::number(getCityID()) + "\nStatusid: " + QString::number(getStatusID()) + "\nSøknadsfrist: " + getDate());
                msg2.exec();
            }
        }
        setChanged(false);
    }
}

void ViewJobs::buttonFirstClicked()
{
    checkChanges();
    getApplication(1);
    ui->btnFirst->setEnabled(false);
    ui->btnPrev->setEnabled(false);
    ui->btnNext->setEnabled(true);
    ui->btnLast->setEnabled(true);
}

void ViewJobs::buttonLastClicked()
{
    checkChanges();
    getApplication(lastid);
    ui->btnFirst->setEnabled(true);
    ui->btnLast->setEnabled(false);
    ui->btnNext->setEnabled(false);
    ui->btnPrev->setEnabled(true);
}

void ViewJobs::buttonNextClicked()
{
    checkChanges();
    int currentApplication = getApplicationID();
    getApplication(currentApplication + 1);
    ui->btnFirst->setEnabled(true);
    ui->btnPrev->setEnabled(true);
    if(currentApplication + 1 == lastid)
    {
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
}

void ViewJobs::buttonPreviousClicked()
{
    checkChanges();
    int currentApplication = getApplicationID();
    getApplication(currentApplication - 1);
    ui->btnLast->setEnabled(true);
    ui->btnNext->setEnabled(true);
    if(currentApplication -1 == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
    }
}

void ViewJobs::comboboxApplicationIDChanged()
{
    int id = ui->comboBoxApplicationID->currentText().toInt();
    checkChanges();
    soknadIDChanged = true;
    getApplication(id);
    //setApplicationID(id);
    soknadIDChanged = false;
    if(id == 1)
    {
        ui->btnFirst->setEnabled(false);
        ui->btnPrev->setEnabled(false);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
    }
    else if(id == lastid)
    {
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        ui->btnLast->setEnabled(false);
        ui->btnNext->setEnabled(false);
    }
    else
    {
        ui->btnFirst->setEnabled(true);
        ui->btnPrev->setEnabled(true);
        ui->btnLast->setEnabled(true);
        ui->btnNext->setEnabled(true);
    }
}

/**
 * @brief ViewJobs::getCityIDs Fills the comboBoxTownID with all city IDs that exist in the databse.
 */
void ViewJobs::getCityIDs()
{
    try
    {
        QLinkedList<int> list;// = new QLinkedList<int>();
        list = p->fillList("SELECT stedid FROM sted ORDER BY stedid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxTownID->addItem(QString::number(i+1));
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

/**
 * @brief ViewJobs::getStatusIDs Fills the comboBoxStatusID with all status IDs that exist in the database.
 */
void ViewJobs::getStatusIDs()
{
    try
    {
        QLinkedList<int> list;
        list = p->fillList("SELECT statusid FROM status ORDER BY statusid ASC");
        int i = 0;
        while(i < list.count())
        {
            ui->comboBoxStatusID->addItem(QString::number(i+1));
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

/**
 * @brief ViewJobs::getApplicationID Gets the current application ID.
 * @return The current application ID.
 */
int ViewJobs::getApplicationID()
{
    return applicationid;
}

/**
 * @brief ViewJobs::getTitle Gets the application ID.
 * @return the current title.
 */
QString ViewJobs::getTitle()
{
    return title;
}

/**
 * @brief ViewJobs::getCompany Gets the current employer company.
 * @return the current company.
 */
QString ViewJobs::getCompany()
{
    return company;
}

/**
 * @brief ViewJobs::getCityID Gets the ID of the city where the job is located.
 * @return the ID of the city where the job is located.
 */
int ViewJobs::getCityID()
{
    return cityid;
}

/**
 * @brief ViewJobs::getStatusID Gets the current status ID of the job application.
 * @return the application's current status ID.
 */
int ViewJobs::getStatusID()
{
    return statusid;
}

/**
 * @brief ViewJobs::getDate Gets the current application's dealine.
 * @return The deadline of the current application.
 */
QString ViewJobs::getDate()
{
    return date;
}

/**
 * @brief ViewJobs::setApplicationID sets a new application ID
 * @param newID the new ID.
 */
void ViewJobs::setApplicationID(int newID)
{
    applicationid = newID;
}

/**
 * @brief ViewJobs::setTitle Sets a new job title
 * @param newTitle The new job/position title to be used.
 */
void ViewJobs::setTitle(QString newTitle)
{
    title = newTitle;
}

/**
 * @brief ViewJobs::setCompany Sets a new employer company name.
 * @param newCompany the new company name.
 */
void ViewJobs::setCompany(QString newCompany)
{
    company = newCompany;
}

/**
 * @brief ViewJobs::setCityID Sets a new city ID
 * @param newTownID the new city ID.
 */
void ViewJobs::setCityID(int newTownID)
{
    cityid = newTownID;
}

/**
 * @brief ViewJobs::setStatusID Sets a new status ID for the current job.
 * @param newStatusID the ID of the application's updated status.
 */
void ViewJobs::setStatusID(int newStatusID)
{
    statusid = newStatusID;
}

/**
 * @brief ViewJobs::setDate Sets a new application deadline for the job application.
 * @param newDate The new deadline for the current job application.
 */
void ViewJobs::setDate(QString newDate)
{
    date = newDate;
}

/**
 * @brief ViewJobs::getApplications Fills the comboBoxApplicationID with all application IDs in the database.
 */
void ViewJobs::getApplications()
{
    try
    {
        QLinkedList<int> list;
        list = p->fillList("SELECT soknadid FROM soknad ORDER BY soknadid ASC");
        int i;
        for(i = 0; i < list.count(); i++)
        {
            ui->comboBoxApplicationID->addItem(QString::number(i+1));
        }
        lastid = i;
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

/**
 * @brief ViewJobs::getApplication Fills the window with information based on the application ID
 * @param appID the application ID to be used.
 */
void ViewJobs::getApplication(int appID)
{
    try
    {
        ui->comboBoxApplicationID->setCurrentText(QString::number(appID));
        ui->lineEditTitle->setText(p->getTitle(appID));
        ui->lineEditCompany->setText(p->getCompany(appID));
        ui->comboBoxTownID->setCurrentText(QString::number(p->getCityID(appID)));
        ui->comboBoxStatusID->setCurrentText(QString::number(p->getStatusID(appID)));
        ui->lineEditDeadline->setText(p->getDate(appID));
        setApplicationID(appID);
        setTitle(ui->lineEditTitle->text());
        setCompany(ui->lineEditCompany->text());
        setCityID(ui->comboBoxTownID->currentText().toInt());
        setStatusID(ui->comboBoxStatusID->currentText().toInt());
        setDate(ui->lineEditDeadline->text());
        ui->labelSted->setText(p->getCityName(getCityID()));
        ui->labelStatus->setText(p->getStatusName(getStatusID()));
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
