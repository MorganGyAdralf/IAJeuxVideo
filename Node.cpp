#include "Node.h"
#include <iostream>

Node::Node() {
	next = NULL;
}

Node::Node(const Node& orig) {
    next = orig.next;
    value = orig.value;
}

Node::~Node() {

}

bool Node::hasNext() {

    return next != NULL;
}

Node* Node::getNext() {
    return next;
}

void Node::setNext(Node* newNext) {

    if (newNext == NULL) {
        next = NULL;
    }
    else {
        next = newNext->next;
    }
}

int Node::getValue(){
    return value;
}

void Node::setValue(int val) {
    value = val;
}

