#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

#include "strategy.h"
#include "container.h"

class BubbleSort: public Sort
{
public:
	BubbleSort();
	void sort(Container* container);
};

#endif // __BUBBLE_SORT_H__