#ifndef __DECORATOR_H__
#define __DECORATOR_H__

#include "component.h"
#include<iostream>
using namespace std;

class Decorator: public Base{
public:
	/* Constructors */
	Decorator() {};

	/* Pure Virtual Functions */
	virtual double evaluate() = 0;
	
protected:
	Base* decorated;
};

#endif // __DECORATOR_H__