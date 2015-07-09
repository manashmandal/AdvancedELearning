#include "qboolalgebra.h"

QBoolAlgebra::QBoolAlgebra()
{

}

QBoolAlgebra::~QBoolAlgebra()
{

}

//Generates input values
QString QBoolAlgebra::generateValues(size_t size, int repeatation)
{
    QString output;
    for (int i = 0; i < (size) / pow(2, repeatation) ; i++){
        for (int j = 0; j < repeatation; j++) output.append("0");
        for (int k = 0; k < repeatation; k++) output.append("1");
    }
    return output;
}

