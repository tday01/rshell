#ifndef __SUBTRACT_H__
#define __SUBTRACT_H__

#include "component.h"

class Sub : public Base{
public:
	Sub(Base* lhs, Base* rhs);
	double evaluate();

private:
	Base* lhs;
	Base* rhs;
};

#endif // __SUBTRACT_H__