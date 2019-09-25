#include "ceil.h"

Ceil::Ceil(Base* dec){
	this->decorated = dec;
}

double Ceil::evaluate(){
	double dbase = this->decorated->evaluate();
	if (dbase < 0)return (int)dbase;
	return ((int)dbase) + 1;
}