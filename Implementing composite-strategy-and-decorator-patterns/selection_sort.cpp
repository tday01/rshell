#include "selection_sort.h"

SelectionSort::SelectionSort(){}

void SelectionSort::sort(Container* container){
	int i, j, first, temp;
	int numLength = container->size();
	for (i = numLength - 1; i > 0; i--)
	{
		first = 0;                 // initialize to subscript of first element
		for (j = 1; j <= i; j++)   // locate smallest between positions 1 and i.
		{
			double a = container->at(j)->evaluate();
			double b = container->at(first)->evaluate();
			if (a > b)
				first = j;
		}
		if(first != i) container->swap(first, i);
	}
	return;
}
