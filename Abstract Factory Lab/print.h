#ifndef __BasePrint_H__
#define __BasePrint_H__

class BasePrint {
protected:
    double value;

public:
	//Constructors
    BasePrint() {}
    BasePrint(double val);

	//Pure Virtual Function
	virtual void print() = 0;
};

class DoublePrint : public BasePrint{
public:
	DoublePrint() = default;
	DoublePrint(double val);
	void print();

};

class BinaryPrint : public BasePrint{
public:
	BinaryPrint() = default;
	BinaryPrint(double val);
	void print();

};

class HexPrint : public BasePrint{
public:
	HexPrint() = default;
	HexPrint(double val);
    void print();

};

// END__BasePrint_H__
#endif
