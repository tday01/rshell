#include "add.h"

Add::Add(Base* lhs, Base* rhs){
	this->lhs = lhs;
	this->rhs = rhs;
}

double Add::evaluate(){
	return lhs->evaluate() + rhs->evaluate();
}
