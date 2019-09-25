#include "visitor.h"
#include "composite.h"
#include <iostream>

void PrintVisitor::addNode()
{
    output.append(" + ");
}

void PrintVisitor::multNode()
{
    output.append(" * ");
}

void PrintVisitor::sqrNode()
{
    output.append(" ^2 ");
}

void PrintVisitor::subNode()
{
    output.append(" - ");
}

void PrintVisitor::rootNode(){}

void PrintVisitor::execute()
{
    std::cout << output << std::endl;
}

void PrintVisitor::opNode(Op *op)
{
    int val = op->evaluate();

    output.append(to_string(val));
}
