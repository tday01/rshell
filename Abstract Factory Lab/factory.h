#ifndef __BaseFactory_H__
#define __BaseFactory_H__
#include "print.h"

class BaseFactory {
public:
	//Constructors
	BaseFactory() {}

	//Pure Virtual Function
	virtual BasePrint* generatePrint(double value) = 0;
};

class DoubleFactory : public BaseFactory{
public:

	BasePrint* generatePrint(double value);

};

class HexFactory : public BaseFactory{
public:

	BasePrint* generatePrint(double value);

};

class BinaryFactory : public BaseFactory{
public:

	BasePrint* generatePrint(double value);

};

// END__BaseFactory_H__
#endif
