#include "component.h"

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