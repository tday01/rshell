#ifndef __ADD_H__
#define __ADD_H__

#include "component.h"

class Add : public Base{
public:
	Add(Base* lhs, Base* rhs);
	double evaluate();

private:
	Base* lhs;
	Base* rhs;
};

#endif // __ADD_H__