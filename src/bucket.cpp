#include "bucket.h"

Bucket_node::Bucket_node(Vector *v){
	this->data = v;
	this->next = nullptr;
}

Bucket_node::~Bucket_node(){ }

// Create an Empty Linked list
Bucket::Bucket(){
	this->first = nullptr;
	this->size = 0;
}

// Just delete all the elements of the list (if any) 
Bucket::~Bucket(){
	Bucket_node *cur = this->first, *tmp;
	while( (tmp=cur) != nullptr ){
		delete cur;
		cur = tmp->next;
	}
}

// Store the Vector Pointer in the Bucket (insert at Start)
int Bucket::add(Vector *v){
	Bucket_node *tmp = this->first;
	this->first = new Bucket_node{v};
	if( (this->first) == nullptr ){ return 1; }
	this->first->next = tmp;
	return 0;
}
