#ifndef __DIVIDE_H__
#define __DIVIDE_H__

#include "component.h"

class Div : public Base{
public:
	Div(Base* lhs, Base* rhs);
	double evaluate();

private:
	Base* lhs;
	Base* rhs;
};

#endif // __DIVIDE_H__