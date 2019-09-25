#include "divide.h"

Div::Div(Base* lhs, Base* rhs){
	this->lhs = lhs;
	this->rhs = rhs;
}

double Div::evaluate(){
	return lhs->evaluate() / rhs->evaluate();
}
