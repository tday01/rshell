#include "container.h"
#include <iostream>

VectorContainer::VectorContainer(){
	array = new pBase[_DEFAULT_VECTOR_SIZE];
	//reserved_size = reserved_size;
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

	for (int i = 0; i < this->vsize; i++)
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
	for (int i = 0; i < this->vsize; ++i){
		fact->generatePrint(this->array[i]->evaluate())->print();
        std::cout << " ";
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

//list container
ListContainer::ListContainer(){}

ListContainer::~ListContainer(){}

void ListContainer::set_sort_function(Sort* sort_function){
    this->sort_function = sort_function;
}

void ListContainer::add_element(Base* element){
    node* newNode = new node(element, nullptr, tail);
    if (head == nullptr){
        head = newNode;
    }
    if (tail != nullptr){
        tail->next = newNode;
    }
        tail = newNode;
        ++elements;

}

void ListContainer::print(){
    node *curr = head;
    while (curr) {
        auto printObj = fact->generatePrint(curr->data->evaluate());
        printObj->print();
        std::cout << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}


Base* ListContainer::at(int i){
    int cont = 0;
    node *curr = head;
    while (curr) {
        if (cont == i){
            return curr->data;
        }
        ++cont;
        curr = curr->next;
    }
    return nullptr;
}

void ListContainer::swap(int i, int j){
    node *first, *second;
    int cont = 0;
    node *curr = head;
    while (curr) {
        if (cont == i){
            first = curr;
        }
        ++cont;
        curr = curr->next;
    }
    
    cont = 0;
    curr = head;
    while (curr) {
        if (cont == j){
            second = curr;
        }
        ++cont;
        curr = curr->next;
    }
    
    pBase tmp = first->data;
    first->data = second->data;
    second->data = tmp;
}

void ListContainer::sort(){
    this->sort_function->sort(this);
}

int ListContainer::size(){
    return this->elements;
}
