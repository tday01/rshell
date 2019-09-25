#include "abs.h"


Abs::Abs(Base* dec){
	this->decorated = dec;
}

double Abs::evaluate(){
	double dbase = this->decorated->evaluate();
	if (dbase < 0) return -dbase;
	return dbase;
}
