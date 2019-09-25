#ifndef __SELECTION_SORT_H__
#define __SELECTION_SORT_H__

#include "strategy.h"
#include "container.h"

class SelectionSort: public Sort
{
public:
	SelectionSort();
	void sort(Container* container);
};


#endif // __SELECTION_SORT_H__
