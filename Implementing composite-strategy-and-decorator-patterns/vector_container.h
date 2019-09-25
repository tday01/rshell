#ifndef __VECTOR_CONTAINER_H__
#define __VECTOR_CONTAINER_H__

#include "container.h"

const int _DEFAULT_VECTOR_SIZE = 4;

class VectorContainer : public Container{
public:
	VectorContainer();
	~VectorContainer();
	void set_sort_function(Sort* sort_function);
	void add_element(Base* element);
	void print();
	void sort();
	void swap(int i, int j);
	Base* at(int i);
	int size();

private:
	void resize(unsigned int size);
	pBase *array;
	int vsize;
	int reserved_size;
};

#endif // __VECTOR_CONTAINER_H__