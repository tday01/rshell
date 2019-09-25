#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Base {
public:
	/* Constructors */
	Base() {}

	/* Pure Virtual Functions */
	virtual double evaluate() = 0;
};

typedef Base* pBase;

#endif // __COMPONENT_H__
