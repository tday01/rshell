#include <iostream>
#include "component.h"
#include "strategy.h"
#include "container.h"
#include "decorator.h"
#include "factory.h"
#include "print.h"
#include <cstring>

using namespace std;

int main(int argc, char** argv) 
{
    
    BaseFactory* factory;
    if(argc == 1)	// without flags
    	factory = new DoubleFactory();
    else
   	{
   		if(strcmp(argv[1], "d") == 0)
   			factory = new DoubleFactory();
   		else if(strcmp(argv[1], "h") == 0)
   			factory = new HexFactory();
   		else if(strcmp(argv[1], "b") == 0)
   			factory = new BinaryFactory();
   	}
    
	 
    //leaf in compnent: double value;
	Op* op1 = new Op(5);
	Op* op2 = new Op(2);
	Op* op3 = new Op(4);
	Op* op4 = new Op(6);
    //composite in component: Base* lhs Base* rhs;
	Mult* A = new Mult(op1, op2);
	Sub* B = new Sub(op3, op4);
	Add* C = new Add(A, B);
	Sqr* D = new Sqr(C);

    //deref pointer and access member function
	cout << D->evaluate() << endl;
    //make vector container object
	VectorContainer* container = new VectorContainer(factory);
	//added to array of pointers
	container->add_element(A);
	container->add_element(B);
	container->add_element(D);
	cout << "Container Before Sort: " << endl;
	container->print();
	//container->set_sort_function(new SelectionSort());
    //expects a pointer to Sort
	container->set_sort_function(new BubbleSort());
	container->sort();
	cout << "Container After Sort: " << endl;
	container->print();

	cout << endl << endl;

	ListContainer* containerList = new ListContainer(factory);
	Op* op1l = new Op(2.1);
	Op* op2l = new Op(3);
	Op* op3l = new Op(-4.7);
	Op* op4l = new Op(-6);
	Mult* Al = new Mult(op1l, op2l);
	Sub* Bl = new Sub(op3l, op4l);
	Add* Cl = new Add(Al, Bl);
	Sqr* Dl = new Sqr(Cl);
	Sqr* D2 = new Sqr(Al);
	Sqr* D3 = new Sqr(Bl);
	containerList->add_element(Al);
	containerList->add_element(Bl);
	containerList->add_element(Dl);
	containerList->add_element(D2);
	containerList->add_element(D3);
	cout << "Container Before Sort: " << endl;
	containerList->print();
	containerList->set_sort_function(new SelectionSort());
	//containerList->set_sort_function(new BubbleSort());
	containerList->sort();
	cout << "Container After Sort: " << endl;
	containerList->print();

	cout << endl << endl;
    
	Ceil* ceilDecorator = new Ceil(op1l);
	cout << "Ceil : " << op1l->evaluate() << " -> " << ceilDecorator->evaluate() << endl;

	Floor* floorDecorator = new Floor(op1l);
	cout << "Floor : " << op1l->evaluate() << " -> " << floorDecorator->evaluate() << endl;
		
	Abs* absDecorator = new Abs(op3l);
	cout << "Abs : " << op3l->evaluate() << " -> " << absDecorator->evaluate() << endl;
/*
	// test the print
    BasePrint* bp = new HexPrint(15);
    BasePrint* bp1 = new BinaryPrint(8);
    BasePrint* bp2 = new DoublePrint(9);

    bp->print(); cout << endl;
    bp1->print(); cout << endl;
    bp2->print();cout << endl;
	

	// test the print factory
	BaseFactory* bf = new DoubleFactory();
	bf->generatePrint(9)->print();
	cout << endl;
	BaseFactory* bf1 = new HexFactory();
	bf1->generatePrint(19)->print();
	cout << endl;
	BaseFactory* bf2 = new BinaryFactory();
	bf2->generatePrint(29)->print();
	cout << endl;
	*/
	return 0;
}
