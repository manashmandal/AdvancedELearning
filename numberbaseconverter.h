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
    QString octalToOthers(QString in, BaseType base);
    QString hexadecimalToOthers(QString in, BaseType base);

    QString toHex(QString in, BaseType base);
    QString toOct(QString in, BaseType base);
    QString toDec(QString in, BaseType base);
    QString toBin(QString in, BaseType base);

    QString convertBaseDigit(QString in, BaseType input_base, BaseType output_base);


    QString toOctGroupedBin(QString in);
    QString toHexGroupedBin(QString in);
    QString intoDecimal(QString in, BaseType base);
    QString binaryToOctal(QString in);
    QString binaryToHexadecimal(QString in);

    QString octalToBinary(QString in);
    QString toBinGroupedOct(QString in);
    QString hexadecimalToBinary(QString in);
    QString toBinGroupedHex(QString in);
public slots:
    void decimalFloatingPointRemover(QString in);
    void binaryFloatingPointRemover(QString in);
    void hexadecFloatingPointRemover(QString in);
    void octalFloatingPointRemover(QString in);

    //Conversion slots
    void convertDecimal(QString dec_input);
    void convertBinary(QString bin_input);
    void convertOctal(QString oct_input);
    void convertHexadecimal(QString hex_input);
private slots:
    void on_okButton_clicked();


    void on_precisionBox_valueChanged(int arg1);

    void on_clearButton_clicked();

private:
    Ui::NumberBaseConverter *ui;


    //Relation Between Bases
    QBasePair decimal_binary;
    QBasePair decimal_octal;
    QBasePair decimal_hexadecimal;
    QBasePair binary_octal;
    QBasePair binary_hexdecimal;
    QBasePair octal_hexadecimal;

    QBasePair binary_for_octal;
    QBasePair binary_for_hexadecimal;


    //Base Numbers
    QBaseNumberList decimal;
    QBaseNumberList binary;
    QBaseNumberList octal;
    QBaseNumberList hexadecimal;

    QBaseNumberList bin_hex;
    QBaseNumberList bin_oct;

    int float_precision;

};

#endif // NUMBERBASECONVERTER_H
