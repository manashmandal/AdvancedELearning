#include "qbase.h"



QBase::QBase(uInt rad1, uInt rad2) : radii(rad1), reserved("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"), other_radii(rad2), _precision(6)
{
    generateMap();
    generateOtherMap();
}

QBase::QBase() : reserved("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"), _precision(6)
{

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

    bool fp_exists = false;

    if (in.contains('.')){
        input << in.split('.');
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




/* Takes an input and convert it to other base
 * To set other base QBase obj.setOtherRadii(uInt base) need to be called */
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

/* Returns calculated r's complement value */
QString QBase::calcRComplement(uInt r, QString N)
{
   QStringList input;
   int n;
   double res;
   QString before;

   //Removes all zeroes before any non-zero digits to get the size of integer part
   if (N.contains('.')){
       int index = 0;
       input << N.split('.');
       before = input[index];
       while (before[index] == '0'){
           before = before.remove(index, 1);
       }
       n = before.size();
    } else {
       n = N.size();
   }

   double lval = pow(r, n);
   double rval = toDecimal(r, N).toDouble();
   res = lval - rval;

   return  toOtherBase(r, QString::number(res));
}

QString QBase::calcRMinusOneComplement(uInt r, QString N)
{
    QStringList input;
    int n, m;
    double res;
    QString before, after;

    //Removes all zeroes before any non-zero digits to get the size of integer part
    if (N.contains('.')){
        int index = 0;
        input << N.split('.');
        before = input[index];
        after = input[index + 1];

        while (before[index] == '0'){
            before = before.remove(index, 1);
        }

        if (after.size() != 0){
            while(after[after.size() - 1] == '0'){
                int indx = after.size() - 1;
                after = after.remove(indx, 1);
            }
           m = after.size();
        }

        if (after.size() == 0) m = 0;

        m = after.size();
        n = before.size();
     } else {
        n = N.size();
        m = 0;
    }

    double lval = pow(r, n) - pow(r, -m);
    double rval = toDecimal(r, N).toDouble();
    res = lval - rval;
    return toOtherBase(r, QString::number(res));
}

/* First it converts other base to decimal then from the decimal it
 * convert back to the target base */

QString QBase::toOther(QString in, uInt r, uInt other_r)
{
    radii = r;
    other_radii = other_r;
    generateMap();
    generateOtherMap();
    return fromDecimalToOthers(fromOthersToDecimal(in));
}

/*Converts other bases to decimal, takes two argument - input, base of input*/
QString QBase::toDecimal(uInt base, QString in){

    radii = base;
    generateMap();

    int the_base = base;
    double floating_part;
    int integer_part = 0;
    QStringList input;
    QString before, after, rev_before;
    QByteArray integer_part_string, floating_part_string;

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


/*Converts decimal to other base, takes output base as argument*/

QString QBase::toOtherBase(uInt base, QString in){
    int the_base = base;

    other_radii = base;
    generateOtherMap();

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


/*Performs binary to gray conversion [!duh]*/
QString QBase::binaryToGray(QString in)
{
    QString output = "";
    if (!in.isEmpty()){
    output.clear();
    output.append(in.at(0));
    for (int i = 0, j = 1; j < in.size(); i++, j++){
        output.append(XOR(in.at(i), in.at(j)));
       }
    }

    return output;
}

/* [duh!]  */
QString QBase::grayToBinary(QString in)
{
    QString out = "";
    if (!in.isEmpty()){
        out.clear();
        out.append(in.at(0));
        for (int i = 0, j = 1; j < in.size(); i++, j++){
            out.append(XOR(out.at(i), in.at(j)));
        }
    }
    return out;
}

QString QBase::toBCD(QString in)
{
    QStringList code_list;
    code_list << "0000"
              << "0001"
              << "0010"
              << "0011"
              << "0100"
              << "0101"
              << "0110"
              << "0111"
              << "1000"
              << "1001";

    QString out;

    for (int i = 0; i < in.size(); i++){
        if (in[i].isNumber()){
            out.append(code_list.at(in[i].digitValue()));
            out.append(" ");
        }
    }

    return out;

}


//Basic Logic operations
QChar QBase::NOT(QChar a)
{
    if (a == '0') return '1';
    else return '0';
}

QChar QBase::AND(QChar a, QChar b)
{
    if (a == '1' && b == '1') return '1';
    else return '0';
}

QChar QBase::NAND(QChar a, QChar b)
{
    return NOT(AND(a, b));
}

QChar QBase::OR(QChar a, QChar b)
{
    if (a == '0' && b == '0') return '0';
    else return '1';
}

QChar QBase::NOR(QChar a, QChar b)
{
    return NOT(OR(a, b));
}

QChar QBase::XOR(QChar a, QChar b)
{
    if (a == b) return '0';
    else return '1';
}

QChar QBase::XNOR(QChar a, QChar b)
{
    return NOT(XOR(a, b));
}


QBase::~QBase(){}

