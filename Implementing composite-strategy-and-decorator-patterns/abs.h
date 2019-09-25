#ifndef __ABS_H__
#define __ABS_H__

#include "decorator.h"

class Abs : public Decorator
{
public:
	Abs(Base* decorator);
	double evaluate();
};

#endif // __ABS_H__