#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "container.h"

class Container;

class Sort {
public:
	/* Constructors */
	Sort(){};

	/* Pure Virtual Functions */
	virtual void sort(Container* container) = 0;
};

class BubbleSort: public Sort
{
public:
    BubbleSort();
    void sort(Container* container);
};

class SelectionSort: public Sort
{
public:
    SelectionSort();
    void sort(Container* container);
};

// END__STRATEGY_H__
#endif

