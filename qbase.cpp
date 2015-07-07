#include "qbase.h"



QBase::QBase(uInt rad1) : radii(rad1), reserved("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"), other_radii(16), _precision(6)
{
    generateMap();
    generateOtherMap();
}


void QBase::setRadii(uInt r) {radii = r; generateMap();}
void QBase::setOtherRadii(uInt r) {other_radii = r; generateOtherMap();}



void QBase::generateMap()
{
    base_map.clear();
    for (uInt i = 0; i < radii; i++){
        base_map.insert(i, reserved.at(i));
    }
}

void QBase::generateOtherMap()
{
    other_base_map.clear();
    for (uInt i = 0; i < other_radii; i++){
        other_base_map.insert(i, reserved.at(i));
    }
}


QString QBase::fromOthersToDecimal(QString in)
{
    int the_base = radii;
    double floating_part;
    int integer_part = 0;
    QStringList input;
    QString before, after, rev_before;
    QByteArray integer_part_string, floating_part_string;
    QString final_out;

    bool fp_exists = false;

    if (in.contains('.')){
        input = in.split('.');
        before = input[0];
        after = input[1];
        if (after.size() != 0) fp_exists = true;

    } else {
        before = in;
    }

    //Reversing the string
    for (int i = before.size() - 1; i >= 0; i-- ){
        rev_before.append(before[i]);
    }

    for(int i = 0; i < rev_before.size(); i++){
        int weight = base_map.key(rev_before.at(i));
        integer_part += (weight * pow(the_base, i));
    }

    integer_part_string = QByteArray::number(integer_part);

    if (fp_exists){
        for (int i = 0; i < after.size(); i++){
            int weight = base_map.key(after.at(i));
            floating_part += 1.00 * weight * (pow(the_base, -(i+1)));
        }
        floating_part_string = QByteArray::number(floating_part, 'g', _precision);
    }

    if (fp_exists) return integer_part_string.append(floating_part_string.remove(0, 1));
    else return integer_part_string;

}

QString QBase::fromDecimalToOthers(QString in)
{
    int the_base = other_radii;
    double multiplier = 1.00 * the_base;
    double floating_part;
    int integer_part;
    QStringList input;
    QString before, after;
    QString integer_part_string, floating_part_string;
    QString final_out;

    bool fp_exists = false;

    if (in.contains('.')){
        input << in.split('.');
        before = input[0];
        after = input[1];
        if (after.size() != 0) fp_exists = true;
    } else {
        before = in;
    }

    integer_part = before.toInt();

    while(integer_part != 0){
     int x = integer_part % other_radii;
     integer_part_string.prepend(other_base_map.value(x));
     integer_part /= other_radii;
    }

    if (fp_exists){
        after.prepend(".");
        floating_part = after.toDouble();

        while(floating_part != 0.0){
            floating_part *= multiplier;

            if (floating_part >= 1.00) {
                floating_part_string.append(other_base_map.value(int(floor(floating_part))));
                floating_part = floating_part -  floor(floating_part);

            } else {
                floating_part_string.append("0");
            }
            if (floating_part_string.size() > _precision) break;
        }

        final_out = integer_part_string + "." + floating_part_string;
    }

    else final_out = integer_part_string;

    return final_out;

}


QString QBase::toOther(QString in, uInt r, uInt other_r)
{
    radii = r;
    other_radii = other_r;
    generateMap();
    generateOtherMap();
    return fromDecimalToOthers(fromOthersToDecimal(in));
}

QBase::~QBase(){}

