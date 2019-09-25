#include "square.h"

Sqr::Sqr(Base* expression){
	this->expression = expression;
}

double Sqr::evaluate(){
	double res = expression->evaluate();
	return res * res;
}
