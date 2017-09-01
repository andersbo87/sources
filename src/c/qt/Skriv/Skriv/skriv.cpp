#include "skriv.h"
#include <QMessageBox>

Skriv::Skriv(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Skriv)
{
    ui->setupUi(this);

}

void Skriv::show()
{
    QMainWindow::show();
    QApplication::processEvents();
    emit windowShown();
    connect(ui->comboBox , SIGNAL(currentIndexChanged(int)),this,SLOT(handleSelectionChanged(int)));
    connect(ui->fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(fontHandleSelectionChanged(QFont)));
    connect(ui->textEdit->document(), SIGNAL(contentsChanged()), this, SLOT(countWords()));
    ui->textEdit->setFocus();
    int i = 0;
    while(i<60){
        ui->comboBox->addItem(QString::number(i));
        i++;
    }
    QFont font = ui->textEdit->font();
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    ui->comboBox->setCurrentIndex(font.pointSize());
}



Skriv::~Skriv()
{
    delete ui;
}

void Skriv::on_actionAvslutt_triggered()
{
    avslutt();
}


void Skriv::on_action_pne_triggered()
{
    openFile();
}

void Skriv::on_actionLagre_som_triggered()
{
    saveAs();
}

void Skriv::on_actionLagre_triggered()
{
    saveFile();
}

void Skriv::on_actionAngre_triggered()
{
    undo();
}

void Skriv::on_actionGj_r_om_triggered()
{
    redo();
}

void Skriv::on_actionFet_triggered()
{
    setBold();
}

void Skriv::on_actionKlipp_ut_triggered()
{
    cut();
}

void Skriv::on_actionKopier_triggered()
{
    cp();
}

void Skriv::on_actionLim_inn_triggered()
{
    paste();
}

void Skriv::on_actionKursiv_triggered()
{
    italic();
}

void Skriv::on_actionUnderstrek_triggered()
{
    underline();
}

void Skriv::on_textEdit_textChanged()
{
    // Koden er flyttet til et annet "slott", men beholder funksjonen for å gjøre kompileringen lettere.
}

void Skriv::on_textEdit_selectionChanged()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    QFont font = format.font();
    ui->comboBox->setCurrentIndex(font.pointSize());
}

void Skriv::on_comboBox_currentIndexChanged(int index)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    QFont font = format.font();
    ui->comboBox->setCurrentIndex(font.pointSize());
    ui->textEdit->setFocus();
}

void Skriv::on_actionSkriv_ut_triggered()
{
    printDocument();
}
