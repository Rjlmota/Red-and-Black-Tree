using namespace std;

class node{
	public: 
		int key;
		char color;

		node* leftChild; // Pointer to left child.	
		node* rightChild; // Pointer to the right child.

		node(); 	// Constructor

		node(int k);

		~node(); 	// Destructor



		void printNode(); // Function to print node's content.
		int getKey(); // Function to return the content of a node.
		char getColor(); // Function to return the color of a node.
		node* getLeftChild(); // Function to return a pointer to the left child.
		node* getRightChild(); // Function to return a pointer to the right child.
		void setRightChild(node* p); // Function to set a value for the right child.
		void setLeftChild(node* p); // Function to set a value for the left child.

	};

node::node(){
	key=0;
	color='r';
	leftChild=NULL;
	rightChild=NULL;
}

node::node(int k){
	key = k;
	color='r';
	leftChild=NULL;
	rightChild=NULL;	
}

node::~node(){}

void node::printNode(){
	cout << key;
}

int node::getKey(){
	return key;
}

char node::getColor(){
	return color;
}

node* node::getLeftChild(){
	return leftChild;
}

node* node::getRightChild(){
	return rightChild;
}

void node::setRightChild(node *p){
	rightChild = p;
}

void node::setLeftChild(node *p){
	leftChild = p;
}
