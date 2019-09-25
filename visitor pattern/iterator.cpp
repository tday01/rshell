#include "composite.h"
#include "iterator.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// Operator
///////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
OperatorIterator::OperatorIterator(Base* ptr) : Iterator(ptr){
	
	current_ptr = self_ptr;
}

void OperatorIterator::first() {
	
   // will initialize to the left child
   current_ptr = self_ptr->get_left();
}

void OperatorIterator::next() {
	
    // will cycle from left child (which is where it is set to start), to right child, then to NULL
    if (current_ptr == self_ptr->get_left()) {
		current_ptr = self_ptr->get_right();
	}  else {
		current_ptr = NULL;
	}
}

bool OperatorIterator::is_done() {
	
    // Return true if there are no more elements on the stack to iterate
    return !current_ptr;
}

Base* OperatorIterator::current() {
	
    // Return current 
    return current_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// Unary
///////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
UnaryIterator::UnaryIterator(Base* ptr) : Iterator(ptr){
	
	current_ptr = self_ptr;
}

void UnaryIterator::first() {
	
    // will initialize to the only child
    current_ptr = self_ptr->get_left();
}

void UnaryIterator::next() {
	
    // will cycle from child (which is where it is set to start) to NULL
    current_ptr = NULL;
}

bool UnaryIterator::is_done() {
	
    // Return true if there are no more elements on the stack to iterate
    return !current_ptr;
}

Base* UnaryIterator::current() {
	
    // Return the current
    return current_ptr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// Null
///////////////////////////////////////////////////////////////////////////////////////////////////////

// constructor
NullIterator::NullIterator(Base* ptr) : Iterator(ptr){
	
  current_ptr = NULL;
}

void NullIterator::first() {

}

void NullIterator::next() {
    
}

bool NullIterator::is_done() {
	
   return !current_ptr;
}

Base* NullIterator::current() {
	
   return current_ptr;
}

//////////////////////////////////////////////////////////////////////////////////
/// Preorder
//////////////////////////////////////////////////////////////////////////////////

// constructor
PreOrderIterator::PreOrderIterator(Base* ptr) : Iterator(ptr){

}

void PreOrderIterator::first() {
   
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

void PreOrderIterator::next() {
   
    // Create an iterator for the item on the top of the stack
   Iterator* itr = iterators.top()->current()->create_iterator();

    // Initialize the iterator and push it onto the stack
   itr->first();
   iterators.push(itr);
   
    // As long as the top iterator on the stack is_done(), 
    // pop it off the stack and then advance whatever iterator 
    // is now on top of the stack
   while (!iterators.empty() && iterators.top()->is_done()) {
		delete iterators.top();
		iterators.pop();
		if (!iterators.empty()) {
			iterators.top()->next();
		}
	} 
}

bool PreOrderIterator::is_done() {
   
    // Return true if there are no more elements on the stack to iterate
   return iterators.empty();
}

Base* PreOrderIterator::current() {
   
    // Return the current for the top iterator in the stack
   return iterators.top()->current();
}
