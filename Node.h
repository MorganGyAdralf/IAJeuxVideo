#pragma once
class Node {
public:
    Node();
    Node(const Node& orig);
    virtual ~Node();
    bool hasNext();
    Node* getNext();
    void setNext(Node* newNext);
    int getValue();
    void setValue(int val);
private:
    Node* next;
    int value;
};

