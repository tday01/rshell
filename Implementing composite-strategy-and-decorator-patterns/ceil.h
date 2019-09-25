#ifndef __CEIL_H__
#define __CEIL_H__

#include "decorator.h"

class Ceil: public Decorator
{
public:
	Ceil(Base* decorator);
	double evaluate();
};

#endif // __CEIL_H__