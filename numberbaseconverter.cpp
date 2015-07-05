#include "numberbaseconverter.h"
#include "ui_numberbaseconverter.h"

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


//If More than one floating point is detected, it will delete it immediately
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




void NumberBaseConverter::convertDecimal(QString dec_input)
{

    if (dec_input.isEmpty()){
        ui->binaryEdit->setText(dec_input);
        ui->octalEdit->setText(dec_input);
        ui->hexadecimalEdit->setText(dec_input);
    }

    else {
        ui->binaryEdit->setText(decimalToBinary(dec_input));

    }

}





QString NumberBaseConverter::binaryToDecimal(QString input)
{
    bool float_existence = false;
    QString before_floating_point, after_floating_point;
    int float_index;

    if (input.contains('.')){
        float_existence = true;
        float_index = input.indexOf('.');
        for (int i = float_index + 1; i < input.size(); i++){
            after_floating_point.append(input[i]);
        }

        for (int i = 0; i < float_index; i++){
            before_floating_point.prepend(input[i]);
        }
    }

    else if (!float_existence) {
        for (int i = 0; i < input.size(); i++){
            before_floating_point.prepend(input[i]);
        }
    }

    return before_floating_point;

}


QString NumberBaseConverter::decimalToBinary(QString input){
    bool float_existence = false;
    int float_point_index;
    size_t before_floating_int;
    double after_floating_float;

    QString before_point, after_point;
    QString binary_before_point, binary_after_point;

    if (input.contains('.')){
        float_existence = true;
        float_point_index = input.indexOf('.');
        for (int i = 0; i < float_point_index; i++){
            before_point.append(input[i]);
        }
        before_floating_int  = before_point.toInt();

        for (int i = float_point_index; i < input.size(); i++){
            after_point.append(input[i]);
        }

        after_floating_float = after_point.toDouble();
    } else {
        for (int i = 0; i < input.size(); i++){
            before_point.append(input[i]);
        }
        before_floating_int  = before_point.toInt();
    }


    //Converts before floating to first binary half
    while(before_floating_int != 0){
        binary_before_point.prepend(QString::number(before_floating_int % 2));
        before_floating_int /= 2;

    }

    if (float_existence){
        while (after_floating_float != 0.00){
            after_floating_float *= 2.00;

            if (after_floating_float >= 1.00){
                binary_after_point.append(QString::number(1));
                after_floating_float = after_floating_float - 1.00;
            }
            else binary_after_point.append(QString::number(0));
            if (binary_after_point.size() > 8) break;
        }
        return binary_before_point  + "." + binary_after_point;
    }

    else return binary_before_point;
}
