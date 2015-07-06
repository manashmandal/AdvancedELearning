#include "numberbaseconverter.h"
#include "ui_numberbaseconverter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

NumberBaseConverter::NumberBaseConverter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumberBaseConverter)
{
    ui->setupUi(this);


    connect(ui->decimalEdit, SIGNAL(textEdited(QString)), this, SLOT(decimalFloatingPointRemover(QString)));
    connect(ui->binaryEdit, SIGNAL(textEdited(QString)), this, SLOT(binaryFloatingPointRemover(QString)));
    connect(ui->hexadecimalEdit, SIGNAL(textEdited(QString)), this, SLOT(hexadecFloatingPointRemover(QString)));
    connect(ui->octalEdit, SIGNAL(textEdited(QString)), this, SLOT(octalFloatingPointRemover(QString)));

    connect(ui->decimalEdit, SIGNAL(textEdited(QString)), this, SLOT(convertDecimal(QString)));

    //Restricts Hexadecimal Edit input to both lower and uppercase A-F and 0-9 and length 10
    QRegExpValidator *hexValidator = new QRegExpValidator(QRegExp("[0-9A-Fa-f.]{1,10}"), ui->hexadecimalEdit);
    ui->hexadecimalEdit->setValidator(hexValidator);


    //Restricts using only 0 and 1
    QRegExpValidator *binValidator = new QRegExpValidator(QRegExp("[01.]{1,30}"), ui->binaryEdit);
    ui->binaryEdit->setValidator(binValidator);

    //Restricts using 0-8
    QRegExpValidator *octValidator = new QRegExpValidator(QRegExp("[0-8.]{1,30}"), ui->octalEdit);
    ui->octalEdit->setValidator(octValidator);

    //Restricts using 0-9
    QRegExpValidator *decValidator = new QRegExpValidator(QRegExp("[0-9.]{1,30}"), ui->decimalEdit);
    ui->decimalEdit->setValidator(decValidator);

    //Adding Elementary digits for different bases [N2U]
    decimal << "0"
            << "1"
            << "2"
            << "3"
            << "4"
            << "5"
            << "6"
            << "7"
            << "8"
            << "9"
            << "10"
            << "11"
            << "12"
            << "13"
            << "14"
            << "15";

     binary << "0"
            << "1"
            << "10"
            << "11"
            << "100"
            << "101"
            << "110"
            << "111"
            << "1000"
            << "1001"
            << "1010"
            << "1011"
            << "1100"
            << "1101"
            << "1110"
            << "1111";

     octal << "0"
           << "1"
           << "2"
           << "3"
           << "4"
           << "5"
           << "6"
           << "7"
           << "10"
           << "11"
           << "12"
           << "13"
           << "14"
           << "15"
           << "16"
           << "17";

     hexadecimal << "0"
                 << "1"
                 << "2"
                 << "3"
                 << "4"
                 << "5"
                 << "6"
                 << "7"
                 << "8"
                 << "9"
                 << "A"
                 << "B"
                 << "C"
                 << "D"
                 << "E"
                 << "F";

    for (int i = 0; i < decimal.size(); i++){
        decimal_hexadecimal.append(qMakePair(decimal[i], hexadecimal[i]));
        decimal_octal.append(qMakePair(decimal[i], octal[i]));
        octal_hexadecimal.append(qMakePair(octal[i], hexadecimal[i]));
        decimal_binary.append(qMakePair(decimal[i], binary[i]));
        binary_octal.append(qMakePair(binary[i], octal[i]));
        binary_hexdecimal.append(qMakePair(binary[i], hexadecimal[i]));
    }



}

NumberBaseConverter::~NumberBaseConverter()
{
    delete ui;
}

void NumberBaseConverter::on_okButton_clicked()
{
    this->close();
}

//Float point reducer for Decimal Edit
void NumberBaseConverter::decimalFloatingPointRemover(QString in){
    reduceFloatingPoint(in, ui->decimalEdit);
}

//Float point reducer for Binary Edit
void NumberBaseConverter::binaryFloatingPointRemover(QString in)
{
    reduceFloatingPoint(in, ui->binaryEdit);
}

//Float point reducer for HexadecimalEdit
void NumberBaseConverter::hexadecFloatingPointRemover(QString in)
{
    reduceFloatingPoint(in, ui->hexadecimalEdit);
}

//Float point reducer for Octal Edit
void NumberBaseConverter::octalFloatingPointRemover(QString in)
{
    reduceFloatingPoint(in, ui->octalEdit);
}


//If More than one floating point is detected, it will delete it immediately [N2U]
void NumberBaseConverter::reduceFloatingPoint(QString input, QLineEdit *current_line_edit)
{
    int point_occured = 0;
    for (int i = 0; i < input.size(); i++){
        if (input[i] == '.') {
            point_occured++;
            if (point_occured > 1)  {
                    current_line_edit->setText(current_line_edit->text().remove(i, 1));
            }
        }
    }
}


//Slot for converting from decimal to other bases [C]
void NumberBaseConverter::convertDecimal(QString dec_input)
{

    if (dec_input.isEmpty()){
        ui->binaryEdit->setText(dec_input);
        ui->octalEdit->setText(dec_input);
        ui->hexadecimalEdit->setText(dec_input);
    }

    else {
        ui->binaryEdit->setText(decimalToOthers(dec_input, Binary));
        ui->hexadecimalEdit->setText(decimalToOthers(dec_input, HexaDecimal));
        ui->octalEdit->setText(decimalToOthers(dec_input, Octal));
    }
}



//Converts decimal to other bases [C]
QString NumberBaseConverter::decimalToOthers(QString in, BaseType Base){
    QString out;
    size_t before_fp_int;
    double after_fp_double;

    bool fp_exists = false;
    const int radii = Base;

    double multiplier = 1.00 * radii;

    QString before_fp, after_fp;
    QString conv_bef_fp, conv_af_fp; // Converted before fp and converted after fp (fp = floating point)


    if (in.contains('.')){
        fp_exists = true;
        int fp_index = in.indexOf('.');
        for (int i = 0; i < fp_index; i++){
            before_fp.append(in[i]);
        }
        before_fp_int = before_fp.toInt();

        for (int i = fp_index; i < in.size(); i++){
            after_fp.append(in[i]);
        }

        after_fp_double = after_fp.toDouble();
    }

    else {
        for (int i = 0; i < in.size(); i++){
            before_fp.append(in[i]);
        }
        before_fp_int = before_fp.toInt();
    }


    while (before_fp_int != 0){
        conv_bef_fp.prepend(convertBaseDigit(QString::number(before_fp_int % radii), Decimal, Base));
        before_fp_int /= radii;
    }

    if (fp_exists){
        while (after_fp_double != 0.0){
            after_fp_double *= multiplier;

            if (after_fp_double >= 1.00){
                conv_af_fp.append(convertBaseDigit(QString::number(int(floor(after_fp_double))), Decimal, Base));
                after_fp_double = after_fp_double - floor(after_fp_double);
            } else {
                conv_af_fp.append(QString::number(0));
            }

            if (conv_af_fp.size() > 8) break;
        }
        out = conv_bef_fp + "." + conv_af_fp;

    }
    else out = conv_bef_fp;

    return out;
}

QString NumberBaseConverter::binaryToOthers(QString in, NumberBaseConverter::BaseType base)
{


}

//Converts corresponding digits to another base [N2U?C]
QString NumberBaseConverter::convertBaseDigit(QString in, BaseType input_base, BaseType output_base){
    QString output;
    switch(output_base){
        case HexaDecimal:
            output = toHex(in, input_base);
            break;
        case Octal:
            output = toOct(in, input_base);
            break;
        case Decimal:
            output = toDec(in, input_base);
            break;
        case Binary:
            output = toBin(in, input_base);
            break;
    }
    return output;
}


//Take a string and give a binary output for several digits [N2U?C]
QString NumberBaseConverter::toBin(QString in, BaseType base)
{
    QString output;
    switch(base){
        case Decimal:
            for (int i = 0; i < decimal_binary.size(); i++){
                if (decimal_binary[i].first == in){
                    output = decimal_binary[i].second;
                    break;
                }
            }
        case HexaDecimal:
            for (int i = 0; i < binary_hexdecimal.size(); i++){
                if (binary_hexdecimal[i].second == in){
                    output = binary_hexdecimal[i].first;
                    break;
                }
            }
        case Octal:
            for (int i = 0; i < binary_octal.size(); i++){
                if (binary_octal[i].second == in) {
                    output = binary_octal[i].first;
                    break;
                }
            }
    }
    return output;
}

//Take a string and give a decimal output for several digits [N2U?C]
QString NumberBaseConverter::toDec(QString in, BaseType base)
{
    QString output;

    switch(base){
        case Binary:
            for (int i = 0; i < decimal_binary.size(); i++){
                if (decimal_binary[i].second == in) {
                    output = decimal_binary[i].first;
                    break;
                }
            }
        case Octal:
            for (int i = 0; i < decimal_octal.size(); i++){
                if (decimal_octal[i].second == in) {
                    output = decimal_octal[i].first;
                    break;
                }
            }
        case HexaDecimal:
            for (int i = 0; i < decimal_hexadecimal.size(); i++){
                if (decimal_hexadecimal[i].second == in){
                    output = decimal_hexadecimal[i].first;
                    break;
                }
            }
    }

    return output;
}

//Take a string and give a Hexadecimal output for several digits [N2U?C]
QString NumberBaseConverter::toHex(QString in, BaseType base)
{
    QString output;
    switch(base)
    {
        case Decimal:
            output = decimal_hexadecimal[in.toInt()].second;
            break;

        case Octal:
            for (int i = 0; i < octal_hexadecimal.size(); i++){
                if (octal_hexadecimal[i].first == in){
                    output = octal_hexadecimal[i].second;
                    break;
                }
            }
         case Binary:
            for (int i = 0; i < binary_hexdecimal.size(); i++){
                if (binary_hexdecimal[i].first == in){
                    output = binary_hexdecimal[i].second;
                    break;
                }
            }

    case HexaDecimal:
        QMessageBox::warning(this, "Try converting that yourself!", "Convert HexaDec to HexaDec by yourself.");
    }

    return output;
}

//Take a string and give a octal output for several digits [N2U?C]
QString NumberBaseConverter::toOct(QString in, BaseType base){
    QString output;
    switch(base)
    {
        case Decimal:
            output = decimal_octal[in.toInt()].second;
            break;
        case HexaDecimal:
            for (int i = 0; i < octal_hexadecimal.size(); i++){
                if (octal_hexadecimal[i].second == in){
                    output = octal_hexadecimal[i].first;
                    break;
                }
            }

         case Binary:
            for (int i = 0; i < binary_octal.size(); i++){
                if (binary_octal[i].first == in){
                    output = binary_octal[i].second;
                    break;
                }
            }
    }
    return output;
}
