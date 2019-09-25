#include "component.h"

Add::Add(Base* lhs, Base* rhs){
	this->lhs = lhs;
	this->rhs = rhs;
}

double Add::evaluate(){
	return lhs->evaluate() + rhs->evaluate();
}

Div::Div(Base* lhs, Base* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

double Div::evaluate(){
    return lhs->evaluate() / rhs->evaluate();
}

Mult::Mult(Base* lhs, Base* rhs){
    this->lhs= lhs;
    this->rhs = rhs;
}

double Mult::evaluate(){
    return lhs->evaluate() * rhs->evaluate();
}

Sqr::Sqr(Base* expression){
    this->expression = expression;
}

double Sqr::evaluate(){
    double res = expression->evaluate();
    return res * res;
}

Sub::Sub(Base* lhs, Base* rhs){
    this->lhs = lhs;
    this->rhs = rhs;
}

double Sub::evaluate(){
    return lhs->evaluate() - rhs->evaluate();
}
