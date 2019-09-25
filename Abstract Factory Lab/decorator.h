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

class Abs : public Decorator
{
public:
    Abs(Base* decorator);
    double evaluate();
};

class Ceil: public Decorator
{
public:
    Ceil(Base* decorator);
    double evaluate();
};

class Floor: public Decorator
{
public:
    Floor(Base* decorator);
    double evaluate();
};

// END__DECORATOR_H__
#endif
