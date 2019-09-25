#ifndef __COMMAND_CLASS__
#define __COMMAND_CLASS__

#include "composite.h"

class Command {
	protected:
		Base* root;
	
	public:
		Command() { };
		double execute() {
			return root->evaluate();
		};
		Base* get_root() {
			return root;
		};
		virtual ~Command()
		{
			delete root;
		};
};

class OpCommand : public Command {
public:
	OpCommand(double value)
	{
		root = new Op(value);
	}
	//OpCommand Code Here
};

class AddCommand : public Command {
public:
	AddCommand(Command* command, double value)
	{
		Base* left = command->get_root();
		Base* right = new Op(value);
		root = new Add(left, right);
	}

	~AddCommand()
	{
		delete ((Add*) root)->get_right();
	}
	//AddCommand Code Here
};

class SubCommand : public Command {
public:
	SubCommand(Command* command, double value)
	{
		Base* left = command->get_root();
		Base* right = new Op(value);
		root = new Sub(left, right);
	}

	~SubCommand()
	{
		delete ((Sub*) root)->get_right();
	}
};

class MultCommand : public Command {
public:
	MultCommand(Command* command, double value)
	{
		Base* left = command->get_root();
		Base* right = new Op(value);
		root = new Mult(left, right);
	}

	~MultCommand()
	{
		delete ((Mult*) root)->get_right();
	}
};

class SqrCommand : public Command {
public:
	SqrCommand(Command* command)
	{
		root = new Sqr(command->get_root());
	}

};

#endif //__COMMAND_CLASS__
