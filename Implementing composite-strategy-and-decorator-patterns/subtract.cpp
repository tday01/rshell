#include "subtract.h"

Sub::Sub(Base* lhs, Base* rhs){
	this->lhs = lhs;
	this->rhs = rhs;
}

double Sub::evaluate(){
	return lhs->evaluate() - rhs->evaluate();
}
