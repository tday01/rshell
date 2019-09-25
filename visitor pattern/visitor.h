#include <string>


class Op;
class Base;
class Iterator;
class PreOrderIterator;


class Visitor
{
public:
    Visitor(){}
    virtual void rootNode() = 0;	//For visiting a root node (do nothing)
    virtual void sqrNode() = 0;		//For visiting a square node
    virtual void multNode() = 0;	//For visiting a multiple node
    virtual void subNode() = 0;		//For visiting a subtraction node
    virtual void addNode() = 0;		//For visiting an add node
    virtual void opNode(Op* op) = 0;//For visiting a leaf node

    virtual void execute() = 0;                 //Prints all visited nodes
};


class PrintVisitor : public Visitor
{
	private:
		std::string output;

	public:
        PrintVisitor(){}

        void rootNode() override;	//For visiting a root node (do nothing)
        void sqrNode() override;	//For visiting a square node
        void multNode() override;	//For visiting a multiple node
        void subNode() override;	//For visiting a subtraction node
        void addNode() override;	//For visiting an add node
        void opNode(Op* op) override;//For visiting a leaf node

        void execute() override;	//Prints all visited nodes
};
