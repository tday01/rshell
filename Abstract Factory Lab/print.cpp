#include "print.h"
#include <iostream>
#include <bitset>
#include <iomanip>

using namespace std;

BasePrint::BasePrint(double val)
	: value(val){}

DoublePrint::DoublePrint(double val):BasePrint(val){}
BinaryPrint::BinaryPrint(double val):BasePrint(val){}
HexPrint::HexPrint(double val): BasePrint(val){}

void DoublePrint::print()
{
	cout << value;    
}

void BinaryPrint::print()
{
    string out = bitset<63>(value).to_string();
    out = out.substr(out.find_first_of('1'), out.size());
    cout << out;
}

void HexPrint::print(){
	cout << std::hex << (int)value;
    
}
