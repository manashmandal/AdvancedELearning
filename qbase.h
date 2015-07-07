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
    QBase(uInt rad);
    ~QBase();

    void generateMap();
    void generateOtherMap();

    void setRadii(uInt r);
    void setOtherRadii(uInt r);

    void setPrecision(uInt p) { _precision = p; }

    QString fromOthersToDecimal(QString in);
    QString fromDecimalToOthers(QString in);


    QString toOther(QString in, uInt r , uInt  other_r);


};

#endif // QBASE_H
