using namespace std;

class node{
	private: 
		int key;
		char color;
		node* leftChild; // Pointer to left child.	
		node* rightChild; // Pointer to the right child.

	public:
		node(); // Constructor
		node(int k); // Constructor
		~node(); 	// Destructor
		void printNode(); // Function to print node's content.
		int getKey(); // Function to return the content of a node.
		char getColor(); // Function to return the color of a node.
		node* getLeftChild(); // Function to return a pointer to the left child.
		node* getRightChild(); // Function to return a pointer to the right child.
		void setColor(char c); // Function to set a color to a node.
		void setRightChild(node* p); // Function to set a value for the right child.
		void setLeftChild(node* p); // Function to set a value for the left child.
		int isLeaf(); // Function to check if a node is a leaf.
		int isNull(); // Function to check if a node is NULL-leaf.
		int isNotNull(); // Function to check if a node is not a NULL-leaf.

	};

node::node(){
	key=-1;
	color='b';
	leftChild = NULL;
	rightChild = NULL;

}

node::node(int k){
	key = k;
	color='r';
	leftChild= new node();
	rightChild= new node();	
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

void node::setColor(char c){
	color = c;
}

void node::setRightChild(node *p){
	rightChild = p;
}

void node::setLeftChild(node *p){
	leftChild = p;
}

int node::isLeaf(){
	if((leftChild == NULL) && (rightChild == NULL))
		return 1;	
	return 0;
}

int node::isNull(){
	if(key == -1)
		return 1;
	else
		return 0;
}

int node::isNotNull(){
	if(key != -1)
		return 1;
	else
		return 0;
}
