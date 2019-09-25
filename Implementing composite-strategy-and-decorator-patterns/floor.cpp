#include "floor.h"

Floor::Floor(Base* dec){
	this->decorated = dec;
}

double Floor::evaluate(){
	double dbase = this->decorated->evaluate();
	if (dbase > 0)return (int)dbase;
	return (int)(dbase - 0.9999999999999999);
}