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
#include <QPair>

typedef QList<QPair <QString,QString > > QBasePair;
typedef QList <QString> QBaseNumberList;




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


    enum BaseType {Decimal = 10, HexaDecimal = 16, Octal = 8, Binary = 2};

    QString decimalToOthers(QString in, BaseType Base);
    QString binaryToOthers(QString in, BaseType base);

    QString toHex(QString in, BaseType base);
    QString toOct(QString in, BaseType base);
    QString toDec(QString in, BaseType base);
    QString toBin(QString in, BaseType base);

    QString convertBaseDigit(QString in, BaseType input_base, BaseType output_base);


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


    //Relation Between Bases
    QBasePair decimal_binary;
    QBasePair decimal_octal;
    QBasePair decimal_hexadecimal;
    QBasePair binary_octal;
    QBasePair binary_hexdecimal;
    QBasePair octal_hexadecimal;


    //Base Numbers
    QBaseNumberList decimal;
    QBaseNumberList binary;
    QBaseNumberList octal;
    QBaseNumberList hexadecimal;

};

#endif // NUMBERBASECONVERTER_H
