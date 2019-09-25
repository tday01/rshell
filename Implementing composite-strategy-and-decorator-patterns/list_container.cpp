#include "list_container.h"
#include <iostream>

ListContainer::ListContainer(){}

ListContainer::~ListContainer(){}

void ListContainer::set_sort_function(Sort* sort_function){
	this->sort_function = sort_function;
}

void ListContainer::add_element(Base* element){
	node* newNode = new node(element, nullptr, tail);
	if (head == nullptr)
		head = newNode;
	if (tail != nullptr)
		tail->next = newNode;
	tail = newNode;
	++elements;
}

void ListContainer::print(){
	node *curr = head;
	while (curr) {
		std::cout << curr->data->evaluate() << " ";
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
