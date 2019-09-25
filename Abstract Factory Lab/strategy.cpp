#include "strategy.h"

BubbleSort::BubbleSort(){ }

void BubbleSort::sort(Container* container){
	int i, j, flag = 1;    // set flag to 1 to start first pass
	int numLength = container->size();
	for (i = 1; (i <= numLength) && flag; i++)
	{
		flag = 0;
		for (j = 0; j < (numLength - 1); j++)
		{
            
			if (container->at(j + 1)->evaluate() < container->at(j)->evaluate())      // ascending order simply changes to <
			{
				container->swap(j, j + 1); // swap elements
				flag = 1;               // indicates that a swap occurred.
			}
		}
	}
	return;   //arrays are passed to functions by address; nothing is returned
}

SelectionSort::SelectionSort(){}

void SelectionSort::sort(Container* container){
    int i, j, first; //temp;
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

