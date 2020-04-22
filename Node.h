#include <iostream>
#include <list>

using namespace std;

class Node {  // This class represents each node in the behaviour tree.
public:
	virtual bool run() = 0;
};