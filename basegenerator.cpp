#include "basegenerator.h"


BaseGenerator::BaseGenerator() : radi(11), reserved_values("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")
{

}

BaseGenerator::BaseGenerator(size_t r) : radi(r), reserved_values("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")
{
    if (r > 36) r = 36;
    generate();
}

void BaseGenerator::setBase(size_t rad){
    radi = rad;
}

void BaseGenerator::generate()
{
    new_base.clear();
    for (int i = 0; i < radi; i++){
        new_base << reserved_values.at(i);
    }

    //--------------Debugging Purpose-----------------//
    //Uncomment if necessary
    foreach(QString s, new_base) qDebug() << s;
}

BaseGenerator::~BaseGenerator()
{

}

