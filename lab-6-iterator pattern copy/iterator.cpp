#include "composite.h"
#include "iterator.h"

PreorderIterator::PreorderIterator(Base* ptr) : Iterator(ptr)
{

}
void PreorderIterator::first() {
	// Empty the stack (just in case we had something leftover from another run)
	while(!iterators.empty()) {
		delete iterators.top();
		iterators.pop();
	}

	// Create an iterator for the Base* that we built the iterator for
	Iterator* itr = self_ptr->create_iterator();

	// Initialize that iterator and push it onto the stack
	itr->first();
	iterators.push(itr);
}

void PreorderIterator::next() {
	// Create an iterator for the item on the top of the stack
	Iterator* itr = iterators.top()->current()->create_iterator();

	// Initialize the iterator and push it onto the stack
	itr->first();
	iterators.push(itr);

	// As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack
	while (!iterators.empty() && iterators.top()->is_done()) {
		delete iterators.top();
		iterators.pop();
		if (!iterators.empty()) {
			iterators.top()->next();
		}
	}
}

bool PreorderIterator::is_done() {
	// Return true if there are no more elements on the stack to iterate
	return iterators.empty();
}

Base* PreorderIterator::current() {
	// Return the current for the top iterator in the stack
	return iterators.top()->current();
}

OperatorIterator::OperatorIterator(Base* ptr) : Iterator(ptr)
{
	current_ptr = self_ptr;
}

void OperatorIterator::first()
{
	current_ptr = self_ptr->get_left();
}

void OperatorIterator::next()
{
	if (current_ptr == self_ptr->get_left()) {
		current_ptr = self_ptr->get_right();
	} else {
		current_ptr = NULL;
	}
}

bool OperatorIterator::is_done()
{
	return !current_ptr;
}

Base* OperatorIterator::current()
{
	return current_ptr;
}

UnaryIterator::UnaryIterator(Base* ptr) : Iterator(ptr)
{
	current_ptr = self_ptr;
}

void UnaryIterator::first()
{
	current_ptr = self_ptr->get_left();
}

void UnaryIterator::next()
{
	current_ptr = NULL;
}

bool UnaryIterator::is_done()
{
	return !current_ptr;
}

Base* UnaryIterator::current()
{
	return current_ptr;
}

NullIterator::NullIterator(Base* ptr) : Iterator(ptr)
{
	current_ptr = NULL;
}

void NullIterator::first()
{

}

void NullIterator::next()
{

}

bool NullIterator::is_done()
{
	return !current_ptr;
}

Base* NullIterator::current()
{
	return current_ptr;
}
