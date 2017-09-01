#ifndef SKRIV_H
#define SKRIV_H
#include "ui_skriv.h"
#include <QMainWindow>
#include <QtGui>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QMessageBox>
#include <QFileDialog>

namespace Ui {
class Skriv;
}

class Skriv : public QMainWindow
{
    Q_OBJECT

public:
    explicit Skriv(QWidget *parent = 0);
    ~Skriv();


    bool avslutt()
    {
        QTextDocument *doc = ui->textEdit->document();
        if(doc->isModified())
        {
            QMessageBox message;
            message.setIcon(message.Question);
            message.setWindowTitle("Skriv");
            message.setText(QString::fromUtf8("Tekstboksen er endret. Lagre?"));
            message.addButton(QMessageBox::Yes);
            message.addButton(QMessageBox::No);
            message.addButton(QMessageBox::Cancel);
            int res = message.exec();
            if(res == QMessageBox::Yes){
                return saveFile();
            }
            else if(res == QMessageBox::Cancel)
            {
                return false;
            }
        }
       exit(0);
       return true;
    }

    bool saveAs()
    {
        QFileDialog qfd(this, tr("Lagre som..."));
        qfd.setAcceptMode(QFileDialog::AcceptSave);
        qfd.setNameFilter("Tekstfiler (*.txt)");
        qfd.setDefaultSuffix("txt");
        if(qfd.exec() != QDialog::Accepted)
            return false;
        filename = qfd.selectedFiles().first();
        return saveFile();
    }

    bool saveFile()
    {
        if(filename.isEmpty()){
           // Kjører kommandoen "Lagre som"
            return saveAs();
        }
        QFile f(filename);
        f.open(QIODevice::WriteOnly); // Åpner (oppretter den om den ikke finnes) filen for skriving
        QTextDocumentWriter writer(filename);
        writer.setFormat("html");
        bool success = writer.write(ui->textEdit->document());
        // Hvis lagringen lyktes
        if(success){
            ui->textEdit->document()->setModified(false);
        }
        else
        {
            QMessageBox msg;
            msg.setWindowTitle("Skriv");
            msg.setIcon(QMessageBox::Critical);
            msg.setText(QString::fromUtf8("Kunne ikke lagre filen."));
        }
        f.close(); // Lukker filen
        return true;
    }

void openFile() // deler av koden er lånt fra http://doc.qt.io/qt-5/qtwidgets-richtext-textedit-textedit-cpp.html
{
    // Generere dialogen som lar brukeren velge fil
    QString path;
    QFileDialog qfd(this, tr("Åpne fil..."));
    qfd.setAcceptMode(QFileDialog::AcceptOpen);
    qfd.setFileMode(QFileDialog::ExistingFile);
    if(qfd.exec() != QDialog::Accepted) // Hvis brukeren klikker på "Avbryt"
    {
        return;
    }
    path = qfd.selectedFiles().first();
    // Deretter åpner vi filen, leser innholdet og fyller opp tekstboksen.
    QFile f(path);
    f.open(QIODevice::ReadOnly);
    QByteArray data = f.readAll();
    QTextCodec *c = Qt::codecForHtml(data);
    QString str = c->toUnicode(data);
    if(Qt::mightBeRichText(str)) {
        ui->textEdit->setHtml(str);
    }
    else
    {
        str = QString::fromLocal8Bit(data);
        ui->textEdit->setPlainText(str);
    }
    filename = path;
}

bool printDocument()
{
    QString text = ui->textEdit->toPlainText();
    QPrinter printer;
    QPrintDialog *qpd = new QPrintDialog(&printer);
    qpd->setWindowTitle("Skriv ut dokument…");
    if(qpd->exec() != QDialog::Accepted){
        return false;
    }
    QPainter painter;
    painter.begin(&printer);
    painter.drawText(100,100,500,500,Qt::AlignLeft|Qt::AlignTop, text);
    painter.end();
    return true;
}

// Kode som kjøres når vinduet lukkes:
virtual void closeEvent(QCloseEvent *event)
{
    bool res = avslutt();
    if(!res)
        event->ignore();
}

void undo()
{
    ui->textEdit->undo();
}

void redo()
{
    ui->textEdit->redo();
}

void setBold()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    if(!cursor.charFormat().font().bold()){
        format.setFontWeight(QFont::Bold);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
    else {
        format.setFontWeight(QFont::Normal);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
}

void italic()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    if(!cursor.charFormat().font().italic()){
        format.setFontItalic(true);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
    else {
        format.setFontItalic(false);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
}
void underline()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    if(!cursor.charFormat().font().underline()){
        format.setFontUnderline(true);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
    else {
        format.setFontUnderline(true);
        ui->textEdit->textCursor().mergeCharFormat(format);
    }
}

void paste()
{
    ui->textEdit->paste();
}

void cp()
{
    ui->textEdit->copy();
}

void cut()
{
    ui->textEdit->cut();
}
void show();
void setCurrentIndex(int i)
{

}
signals:
void windowShown();
private slots:
void handleSelectionChanged(int index)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    format.setFontPointSize(index);
    ui->textEdit->setFontPointSize(index);
    ui->textEdit->textCursor().mergeCharFormat(format);
};
void fontHandleSelectionChanged(QFont name)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextCharFormat format;
    format.setFont(name);
    ui->textEdit->textCursor().mergeCharFormat(format);
};
void countWords()
{
    // Teller antall tegn
    QString text = ui->textEdit->toPlainText();
    int l = text.length();

    // Teller antall ord
    QTextDocument *doc = qobject_cast<QTextDocument *>(sender());
    QRegExp r("\\b\\w+\\b");
    int i = 0;
    QTextCursor c = doc->find(r);
    while(!c.isNull()) {
        i++;
        c = doc->find(r, c);
    }

    // Skriver ut antall tegn og ord i etiketten nederst i vinduet.
    ui->label->setText("Totalt antall tegn: " + QString::number(l) + ". Antall ord: " + QString::number(i));
};
    void on_actionAvslutt_triggered();

    void on_action_pne_triggered();

    void on_actionLagre_som_triggered();

    void on_actionLagre_triggered();

    void on_actionAngre_triggered();

    void on_actionGj_r_om_triggered();

    void on_actionFet_triggered();

    void on_actionKlipp_ut_triggered();

    void on_actionKopier_triggered();

    void on_actionLim_inn_triggered();
    void on_actionKursiv_triggered();

    void on_actionUnderstrek_triggered();

    void on_textEdit_textChanged();

    void on_textEdit_selectionChanged();

    void on_comboBox_currentIndexChanged(int index);

    void on_actionSkriv_ut_triggered();

private:
    QString filename;
    Ui::Skriv *ui;
};

#endif // SKRIV_H
