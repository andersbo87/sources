#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QMessageBox>


bool isUpdating;
QString title = "Oppdater FreeBSD og installerte programmer";
QProcess *myProcess;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(On_pushButton_Click()));
    myProcess = nullptr;
}

void MainWindow::slotButtonClicked()
{
    // do something
    On_pushButton_Click();

}

// Aktiverer trykknapp 1 og 3
void MainWindow::activateButtons()
{
    ui->pushButton->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}

// Deaktiverer trykknappene for at brukeren ikke skal kunne sette igang flere operasjoner samtidig. Dette for å unngå krøll med utdataen som vises i tekstboksen.
void MainWindow::deactivateButtons()
{
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void MainWindow::On_pushButton_Click()
{
    deactivateButtons();
    QObject *parent = new QObject();
    myProcess = new QProcess(parent);
    myProcess->setProcessChannelMode(myProcess->MergedChannels);
    QString program = "/usr/sbin/freebsd-update fetch --not-running-from-cron";
    QCoreApplication::processEvents();
    ui->textBrowser->clear();
    connect(myProcess, SIGNAL(readyReadStandardError()),this,SLOT(updateError()));
    connect(myProcess, SIGNAL(readyReadStandardOutput()),this,SLOT(updateText()));
    myProcess->start(program);
    connect(myProcess, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(on_myFreeBSDUpdateFetchExit(int , QProcess::ExitStatus )));
}


void MainWindow::on_myFreeBSDUpdateFetchExit(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString text = ui->textBrowser->toPlainText();
    if(exitStatus == QProcess::NormalExit){
        if(exitCode == 0)
        {

            // If no updates are available, the final line in output of freebsd-update begins with "No updates needed to update system to [...]"
            bool noUpdate = text.contains("No updates needed to update system to");
            if(!noUpdate){
                ui->pushButton_2->setEnabled(true);
                QMessageBox message;
                message.setIcon(message.Information);
                message.setWindowTitle(title);
                message.setText(QString::fromUtf8("Tilgjengelige oppdateringer har nå blitt lastet ned. Klikk på \"Installer FreeBSD-oppdateringer\" for å installere disse."));
                message.exec();
            }
            else
            {
                QMessageBox message;
                message.setIcon(message.Information);
                message.setWindowTitle(title);
                message.setText(QString::fromUtf8("Det finnes ingen tilgjengelige oppdateringer."));
                message.exec();
            }
        }
        else if(exitCode == 1)
        {
            QMessageBox message;
            message.setIcon(message.Warning);
            message.setWindowTitle(title);
            if(text.contains("No mirrors remaining, giving up."))
                message.setText(QString::fromUtf8("Kan ikke oppnå kontakt med FreeBSDs servere."));
            else if(text.contains("Directory does not exist or is not writable: /var/db/freebsd-update"))
                message.setText(QString::fromUtf8("Du må være administrator for å kjøre dette programmet. Vennligst start programmet på nytt som administrator."));
            else
                message.setText(QString::fromUtf8("En feil har oppstått."));
            message.exec();
        }
    }
    activateButtons();
}

void MainWindow::on_myFreeBSDUpdateInstallExit(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitStatus == QProcess::NormalExit){
        if(exitCode == 0)// && exitStatus == 1)
        {
            isUpdating = false;
            QString text = ui->textBrowser->toPlainText();
            // Hvis selve kjernen er blitt oppdatert, vil det stå /boot/kernel/kernel."
            bool kernelUpdated = text.contains("/boot/kernel/kernel");
            if(kernelUpdated)
            {
                QMessageBox msgBox;
                msgBox.setIcon(msgBox.Warning);
                msgBox.setWindowTitle(title);
                msgBox.setText(QString::fromUtf8("Kjernen i systemet har nå blitt oppdatert. For å ta i bruk den nye kjernen, må du starte datamaskinen på nytt."));
                msgBox.exec();
            }
        }
    }
    activateButtons();
}

void MainWindow::on_myPkgUpgradeExit(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString text = ui->textBrowser->toPlainText();
    if(exitStatus == QProcess::NormalExit)
    {
        QMessageBox msg;
        if(exitCode == 0)
        {
            if(text.contains("No address record"))
            {
                msg.setWindowTitle(title);
                msg.setIcon(msg.Warning);
                msg.setText(QString::fromUtf8("Det ser ut til at programmet ikke får kontakt med tjeneren. Vennligst se til at du er koblet til internett og prøv igjen."));
                msg.exec();
                isUpdating = false;
            }
            else
            {
                msg.setWindowTitle(title);
                msg.setIcon(msg.Information);
                msg.setText(QString::fromUtf8("Installerte programmer har nå blitt oppdatert."));
                msg.exec();
                isUpdating = false;
            }
        }
        else{
            msg.setWindowTitle(title);
            msg.setIcon(msg.Warning);
            msg.setText(QString::fromUtf8("Det har oppstått en feil under oppdateringen."));
            msg.exec();
            isUpdating = false;
        }
    }
    activateButtons();
}

void MainWindow::updateError()
{
    QByteArray data = myProcess->readAllStandardError();
    ui->textBrowser->append(QString(data));
}

void MainWindow::updateText()
{
    QByteArray data = myProcess->readAllStandardOutput();
    ui->textBrowser->insertPlainText(QString(data)); // append(QString(data));
}
void MainWindow::closeEvent (QCloseEvent *event)
{
    if(isUpdating)
    {
        event->ignore();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    if(myProcess != nullptr)
        myProcess->close();
    delete myProcess;
}

void MainWindow::on_pushButton_2_clicked()
{
    isUpdating = true;
    deactivateButtons();
    QObject *parent = new QObject();
    myProcess = new QProcess(parent);
    myProcess->setProcessChannelMode(myProcess->MergedChannels);
    QString program = "/usr/sbin/freebsd-update install --not-running-from-cron";
    QCoreApplication::processEvents();
    //ui->textBrowser->clear();
    connect(myProcess, SIGNAL(readyReadStandardError()),this,SLOT(updateError()));
    connect(myProcess, SIGNAL(readyReadStandardOutput()),this,SLOT(updateText()));
    myProcess->start(program);
    connect(myProcess, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(on_myFreeBSDUpdateInstallExit(int , QProcess::ExitStatus )));
}

void MainWindow::on_pushButton_3_clicked()
{
    isUpdating = true;
    deactivateButtons();
    ui->textBrowser->append("Output av \"pkg upgrade -y\"");
    QObject *parent = new QObject();
    myProcess = new QProcess(parent);
    myProcess->setProcessChannelMode(myProcess->MergedChannels);
    QString program = "/usr/sbin/pkg upgrade -y";
    QCoreApplication::processEvents();
    ui->textBrowser->clear();
    connect(myProcess, SIGNAL(readyReadStandardError()),this,SLOT(updateError()));
    connect(myProcess, SIGNAL(readyReadStandardOutput()),this,SLOT(updateText()));
    myProcess->start(program);
    connect(myProcess, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(on_myPkgUpgradeExit(int , QProcess::ExitStatus )));
}
