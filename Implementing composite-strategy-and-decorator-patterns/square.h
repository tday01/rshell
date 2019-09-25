#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "component.h"

class Sqr : public Base{
public:
	Sqr(Base* expression);
	double evaluate();

private:
	Base* expression;
};

#endif // __SQUARE_H__