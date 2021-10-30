#include "shortedList.h"
#include <iostream>

// Just store the data and init the "next" ptr
SL_Node::SL_Node(Vector *v, double dist){
	this->v = v;
	this->dist = dist;
	this->next = nullptr;
}

void SL_Node::print(){
	std::cout << " Id: " << this->v->id << ", Distance: " << this->dist << std::endl;
}

//------------------------------------------------------------------------------------------------------------------

// Create an empty Shorted List
ShortedList::ShortedList(unsigned N){
	this->first = nullptr;
	this->last = nullptr;
	this->length = 0;
}

ShortedList::~ShortedList(){
	SL_Node *cur = this->first, *tmp;
	while( (tmp=cur) != nullptr ){
		cur = cur->next;
		delete tmp;
	}
}

// Insert the given Vector in the correct location in the list based on its given distance
int ShortedList::add(Vector *v, double dist){
	
	// If the list is empty just add it
	if( this->first == nullptr ){
		this->first = new SL_Node(v, dist);
		this->last = this->first;
		(this->length)++;
		return 0;
	}
	// Else, just add it in the correct location
	
	// Find the correct location
	SL_Node *cur = this->first, *prev;
	while( (cur!=nullptr) && (cur->dist < dist) ){
		prev = cur;
		cur = cur->next;
	}

	// Add it and link accordingly
	if( cur == this->first ){	// New first item
		this->first = new SL_Node(v, dist);
		this->first->next = cur;
	}
	else if( cur == nullptr ){	// New last item
		this->last = new SL_Node(v, dist);
		prev->next = this->last;
	}
	else{	// New item in between
		prev->next = new SL_Node(v, dist);
		prev->next->next = cur;
	}
	(this->length)++;
	return 0;
}

// Print the shorted list
void ShortedList::print(){
	std::cout << std::endl << " (i) Printing Shorted List: " << std::endl;
	
	SL_Node *cur = this->first;
	while( cur != nullptr ){
		cur->print();
		cur = cur->next;
	} std::cout << std::endl;
}
