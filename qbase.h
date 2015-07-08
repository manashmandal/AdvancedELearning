#ifndef QBASE_H
#define QBASE_H
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QStringList>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


typedef QMap <int, QString> QBaseMap;
typedef size_t uInt;

class QBase
{
private:
    QBaseMap base_map;
    QBaseMap other_base_map;
    uInt radii;
    uInt other_radii;
    QString reserved;
    int _precision;

public:
    QBase(uInt rad1, uInt rad2);
    QBase();
    ~QBase();

    void generateMap();
    void generateOtherMap();

    void setRadii(uInt r);
    void setOtherRadii(uInt r);

    void setPrecision(uInt p) { _precision = p; }

    QString fromOthersToDecimal(QString in);
    QString fromDecimalToOthers(QString in);

    QString calcRComplement(uInt r, QString N);
    QString calcRMinusOneComplement(uInt r, QString N);


    QString toOther(QString in, uInt r , uInt  other_r);


    QString toDecimal(uInt base, QString in);
    QString toOtherBase(uInt base, QString in);

    QString binaryToGray(QString in);
    QString grayToBinary(QString in);

    QString excess3(QString in);
    QString toBCD(QString in);

    //Logic operations
    QChar NOT(QChar a);
    QChar AND(QChar a, QChar b);
    QChar NAND(QChar a, QChar b);
    QChar OR(QChar a, QChar b);
    QChar NOR(QChar a, QChar b);
    QChar XOR(QChar a, QChar b);
    QChar XNOR(QChar a, QChar b);



};

#endif // QBASE_H
