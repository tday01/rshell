#include "factory.h"
#include "print.h"
#include <iostream>

BasePrint* DoubleFactory::generatePrint(double value){
    
    return new DoublePrint(value);
}

BasePrint* HexFactory::generatePrint(double value){
    
    return new HexPrint(value);
}

BasePrint* BinaryFactory::generatePrint(double value){
    
    return new BinaryPrint(value);
}


