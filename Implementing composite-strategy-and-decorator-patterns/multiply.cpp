#include "multiply.h"

Mult::Mult(Base* lhs, Base* rhs){
	this->lhs= lhs;
	this->rhs = rhs;
}

double Mult::evaluate(){
	return lhs->evaluate() * rhs->evaluate();
}
