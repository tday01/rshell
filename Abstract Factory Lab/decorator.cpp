#include "decorator.h"
#include <cmath>

Abs::Abs(Base* dec){
	this->decorated = dec;
}

double Abs::evaluate(){
	double dbase = this->decorated->evaluate();
    return std::abs(dbase);
}

Ceil::Ceil(Base* dec){
    this->decorated = dec;
}

double Ceil::evaluate(){
    double dbase = this->decorated->evaluate();
    return ceil(dbase);
}

Floor::Floor(Base* dec){
    this->decorated = dec;
}

double Floor::evaluate(){
    double dbase = this->decorated->evaluate();
    return floor(dbase);
}
