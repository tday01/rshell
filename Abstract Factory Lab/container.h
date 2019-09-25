#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include "strategy.h"
#include "component.h"
#include "factory.h"
#include <iostream>

class Sort;

class Container {
protected:
	Sort* sort_function;
    BaseFactory* fact = new DoubleFactory();

public:
	/* Cosntructors */
	Container() : sort_function(0) { };
	Container(Sort* function);
    Container(BaseFactory* pbase):fact(pbase){}
    
    	/* Virtual Destructor */
    	virtual ~Container() {};

	/* Non Virtual Functions */
	// Set the type of sorting algorithm
	void set_sort_function(Sort* sort_function);

	/* Pure Virtual Functions */
	// insert the top pointer of the tree into the container
	virtual void add_element(Base* element) = 0;
	// iterate through the trees and output values
	virtual void print() = 0;
	// calls on the previously set sorting-algorithm. 
	// Check if sort_function is not null, throw exception if is null
	virtual void sort() = 0;

	/* Essentially the only functions needed to sort */
	// switch tree locations
	virtual void swap(int i, int j) = 0;
	// get top pointer of tree at index i
	virtual Base* at(int i) = 0;
	// return container size;
	virtual int size() = 0;
};

const int _DEFAULT_VECTOR_SIZE = 4;

class VectorContainer : public Container{
public:
    VectorContainer();
    VectorContainer(BaseFactory* bf):Container(bf){}
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
    int vsize = 0;
    int reserved_size = 0;
};

class ListContainer : public Container
{
public:
    ListContainer();
    ListContainer(BaseFactory* bf):Container(bf){}

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
    //null
    int elements = 0;
    node *head = 0;
    node *tail = 0;
    
};

// END__CONTAINER_H__
#endif
