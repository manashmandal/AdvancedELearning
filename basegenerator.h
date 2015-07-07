#ifndef BASEGENERATOR_H
#define BASEGENERATOR_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

typedef QStringList QBaseDigitList;

class BaseGenerator
{
private:
    size_t radi;
    QString reserved_values;

    QBaseDigitList new_base;

    QBaseDigitList binary;
    QBaseDigitList octal;
    QBaseDigitList hexadecimal;
    QBaseDigitList decimal;

    QBaseDigitList bin_for_hex;
    QBaseDigitList bin_for_oct;




public:
    BaseGenerator(size_t r);
    BaseGenerator();
    void generate();
    void setBase(size_t rad);

    void generateCorrespondingBinary();
    void generateCorrespondingDecimal();
    void generateCorrespondingOctal();
    void generateCorrespondingHexadecimal();

    ~BaseGenerator();
};

#endif // BASEGENERATOR_H
