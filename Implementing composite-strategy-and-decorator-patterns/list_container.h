#ifndef __LIST_CONTAINER_H__
#define __LIST_CONTAINER_H__

#include "container.h"

class ListContainer : public Container
{
public:
	ListContainer();
	~ListContainer();
	void set_sort_function(Sort* sort_function);
	void add_element(Base* element);
	void print();
	void sort();
	void swap(int i, int j);
	Base* at(int i);
	int size();

private:
	struct node {
		Base* data;
		node *next, *prev;
		node(pBase& data, node* next, node* prev)
			: data(data)
			, next(next)
			, prev(prev) {
		}
	};
	int elements = 0;
	node *head = 0;
	node *tail = 0;

};

#endif // __LIST_CONTAINER_H__