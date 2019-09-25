#ifndef __MULTIPLY_H__
#define __MULTIPLY_H__

#include "component.h"

class Mult : public Base{
public:
	Mult(Base* lhs, Base* rhs);
	double evaluate();

private:
	Base* lhs;
	Base* rhs;
};

#endif // __MULTIPLY_H__