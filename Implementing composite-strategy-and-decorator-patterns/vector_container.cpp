#include "vector_container.h"
#include <iostream>

VectorContainer::VectorContainer(){
	array = new pBase[_DEFAULT_VECTOR_SIZE];
	reserved_size = reserved_size;
	vsize = 0;
}

VectorContainer::~VectorContainer(){
	delete[] array;
}

void VectorContainer::set_sort_function(Sort* sort_function){
	this->sort_function = sort_function;
}

void VectorContainer::resize(unsigned int new_reserved_size){
	pBase *newBuffer = new pBase[new_reserved_size];

	for (unsigned int i = 0; i < this->vsize; i++)
		newBuffer[i] = array[i];

	this->reserved_size = new_reserved_size;
	delete[] array;
	array = newBuffer;
}

void VectorContainer::add_element(Base* element){
	if (vsize == reserved_size)
		resize(this->reserved_size + _DEFAULT_VECTOR_SIZE);
	
	// size_ when used as an index, points to the next position after
	// the last element in the vector
	array[this->vsize] = element;

	// now there is one more element in the vector, so increase the size
	vsize++;
}

void VectorContainer::print(){
	for (unsigned int i = 0; i < this->vsize; ++i){
		std::cout << this->array[i]->evaluate() << " ";
	}
	std::cout << std::endl;
}

int VectorContainer::size(){
	return vsize;
}

Base* VectorContainer::at(int i){
	return this->array[i];
}

void VectorContainer::swap(int i, int j){
	pBase tmp = this->array[i];
	this->array[i] = this->array[j];
	this->array[j] = tmp;
}

void VectorContainer::sort(){
	this->sort_function->sort(this);
}