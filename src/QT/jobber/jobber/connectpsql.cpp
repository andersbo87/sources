#include "connectpsql.h"
#include "ui_connectpsql.h"
#include "mainwindow.h"
#include <QMessageBox>

/**
 * @brief connectPsql::connectPsql
 * @param parent
 */
connectPsql::connectPsql(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectPsql)
{
    ui->setupUi(this);
    setFixedSize(size());
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Koble til");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Avbryt");
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->lineEdit_User, SIGNAL(textChanged(QString)), this, SLOT(userTextChanged()));
    connect(ui->lineEdit_Host, SIGNAL(textChanged(QString)), this, SLOT(hostTextChanged()));
    connect(ui->lineEdit_Password, SIGNAL(textChanged(QString)), this, SLOT(passwordTextChanged()));
    ui->lineEdit_Host->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_Host->setFocus();
    this->setMinimumSize(400,185);
    this->setMaximumSize(400,185);
}

void connectPsql::accept()
{
    if(p->connectDatabase())
    {
        QDialog::accept();
    }
    else
    {
        QMessageBox msg;
        msg.setIcon(msg.Information);
        msg.setWindowTitle("Jobber");
        msg.setText("Oppkoblingen til databasen mislyktes.");
        msg.exec();
    }
}

/**
 * @brief connectPsql::userTextChanged: Sets the new username
 */
void connectPsql::userTextChanged()
{
    //userName = ui->plainTextEdit->toPlainText();
    p->setUsername(ui->lineEdit_User->text());
}

/**
 * @brief connectPsql::passwordTextChanged: Sets the new password
 */
void connectPsql::passwordTextChanged()
{
    p->setPassword(ui->lineEdit_Password->text());
}

/**
 * @brief connectPsql::hostTextChanged: Sets the new host (server's IP address).
 */
void connectPsql::hostTextChanged()
{
    p->setHost(ui->lineEdit_Host->text());
}
connectPsql::~connectPsql()
{
    delete ui;
}
