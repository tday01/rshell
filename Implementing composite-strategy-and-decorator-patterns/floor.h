#ifndef __FLOOR_H__
#define __FLOOR_H__

#include "decorator.h"

class Floor: public Decorator
{
public:
	Floor(Base* decorator);
	double evaluate();
};

#endif // __FLOOR_H__