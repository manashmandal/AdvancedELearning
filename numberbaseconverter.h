#ifndef NUMBERBASECONVERTER_H
#define NUMBERBASECONVERTER_H

#include <QDialog>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QLineEdit>
#include <QDebug>


namespace Ui {
class NumberBaseConverter;
}

class NumberBaseConverter : public QDialog
{
    Q_OBJECT

public:
    explicit NumberBaseConverter(QWidget *parent = 0);
    ~NumberBaseConverter();


    void reduceFloatingPoint(QString input, QLineEdit *current_line_edit);

    QString decimalToBinary(QString input);
    QString binaryToDecimal(QString input);
public slots:
    void decimalFloatingPointRemover(QString in);
    void binaryFloatingPointRemover(QString in);
    void hexadecFloatingPointRemover(QString in);
    void octalFloatingPointRemover(QString in);

    void convertDecimal(QString dec_input);
private slots:
    void on_okButton_clicked();


private:
    Ui::NumberBaseConverter *ui;
};

#endif // NUMBERBASECONVERTER_H
