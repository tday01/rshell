#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Base {
public:
	//Constructors
	Base() {}

	//Pure Virtual Function
	virtual double evaluate() = 0;
};

typedef Base* pBase;

class Add : public Base{
public:
    Add(Base* lhs, Base* rhs);
    double evaluate();
    
private:
    Base* lhs;
    Base* rhs;
};

class Div : public Base{
public:
    Div(Base* lhs, Base* rhs);
    double evaluate();
    
private:
    Base* lhs;
    Base* rhs;
};

class Mult : public Base{
public:
    Mult(Base* lhs, Base* rhs);
    double evaluate();
    
private:
    Base* lhs;
    Base* rhs;
};

class Sqr : public Base{
public:
    Sqr(Base* expression);
    double evaluate();
    
private:
    Base* expression;
};

class Sub : public Base{
public:
    Sub(Base* lhs, Base* rhs);
    double evaluate();
    
private:
    Base* lhs;
    Base* rhs;
};

class Op : public Base{
public:
    Op(double value) {
        this->value = value;
    }
    
    double evaluate(){
        return value;
    }
    
private:
    double value;
};

// END__COMPONENT_H__
#endif
