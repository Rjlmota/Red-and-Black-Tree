#include <stack>
#include "node.h"
using namespace std;

class tree {
	private:  
		node* root;

	public:

		tree(); //Constructor
		~tree(); //Destructor

		void eraseData(node *localRoot); // Function used by destructor.

		void printTree(); // Function to print tree.
		
		node* getParent(int key); // Function used to get the node's parent.
		node* getGrampa(int key); // Function used to get the node grampa.
		node* getUncle(int key); // Function used to get the node uncle.
		node* getSibling(int key); // Function used to get the node sibling.
		node* getSucessor(int key); // Function to get a sucessor of a node.
		
		void leftRotation(node **p); // Function to do a left rotation on a tree.
		void rightRotation(node **p); // Function to do a right rotation on a tree.
		node* search(int key); // Function to search for node.
		void del(node *p); // Function to delete a node.
		void replace(node* currentN, node* sucessorN); // Function to replace a node with it's sucessor.

		void insert(int key); // Function to insert a node.
		void balance(node* currentN); // Function to check the balance.
		void remove(int key); // Function for removal of node.
};	


tree::tree(){
	root = NULL;
}

tree::~tree(){}

void tree::printTree(){

	cout << "\n";

	stack<node*> pilhaGlobal;
	pilhaGlobal.push(root);
	int nVazios = 32;
	bool linhaVazia = false;
	
	cout << endl;
	while(linhaVazia==false){
	stack<node*> pilhaLocal;
	linhaVazia = true;

		for(int j=0; j<nVazios; j++)
			cout << ' ';

		while(pilhaGlobal.empty()==false){

			node* temp = pilhaGlobal.top();
			pilhaGlobal.pop();
			if(temp->isNotNull()){
				if (temp->getColor() == 'r'){
					cout << '['<< temp->getKey() << ']';	
				}else if(temp->getColor() == 'b'){
					cout << '('<< temp->getKey() << ')';						
				}else{
					cout<< "((" << temp->getKey() << "))";	
				}

				pilhaLocal.push(temp->getLeftChild());
				pilhaLocal.push(temp->getRightChild());

				if(temp->getLeftChild()->isNotNull() || temp->getRightChild()->isNotNull())
					linhaVazia = false;
			}
			else{
				if (temp->getColor()=='B'){
					cout << "(( ))";	
				}else{
					cout << "(  )";
				}
				
				node *nullNode = new node();
				pilhaLocal.push(nullNode);
				pilhaLocal.push(nullNode);
			}
			for(int j=0; j<nVazios*2-2; j++)
				cout << ' ';
		}

		cout << endl;
		nVazios = nVazios/2;
		while(pilhaLocal.empty()==false){
			pilhaGlobal.push( pilhaLocal.top() );
			pilhaLocal.pop();
		}
	}  
	cout << endl;
	cout << "[ ] = Red | ( ) = Black | (( )) = DoubleBlack\n...\n";
}  

node* tree::getParent(int key){

	node *currentN = root;
	node *previousN = new node();
	while ((currentN->isNotNull()) and (currentN->getKey()!=key)){
		previousN = currentN;
		if(key > currentN->getKey())
			currentN = currentN->getRightChild();
		else if(key < currentN->getKey())
			currentN = currentN->getLeftChild();
	}
	if (previousN->isNull()){
		previousN->setLeftChild(currentN);
		previousN->setRightChild(new node());
	}
	return previousN;
}

node* tree::getGrampa(int key){

	node* parentN = getParent(key);

	if(parentN != NULL)
		return getParent(parentN->getKey());

	return NULL;
}

node* tree::getUncle(int key){
	node* grampaN = getGrampa(key);
	node* parentN = getParent(key);

	if (grampaN != NULL){
		if (grampaN->getRightChild() == parentN)
			return grampaN->getLeftChild();
		else
			return grampaN->getRightChild();
	}
	return NULL;
}

node* tree::getSibling(int key){
	node* parentN = getParent(key);

	if (parentN->getRightChild()->getKey() == key)
		return parentN->getLeftChild();
	else
		return parentN->getRightChild();
}

node* tree::getSucessor(int key){
	node* currentN = search(key);
	node* sucessorN = currentN->getLeftChild();
	if (sucessorN->isNotNull()){
		while (sucessorN->getRightChild()->isNotNull())
			sucessorN = sucessorN->getRightChild();
	}else{
		sucessorN = currentN->getRightChild();
	}
	return sucessorN;
}

void tree::leftRotation(node **p0){
	cout << "Left rotation on " << (*p0)->getKey() << ".\n";
	node* parent = getParent((*p0)->getKey());
	node *p1=NULL, *p2=NULL;
	p1 = (*p0)->getRightChild();
	p2 = p1->getLeftChild();
	p1->setLeftChild(*p0);
	(*p0)->setRightChild(p2);

	if(parent->isNotNull()){
		if(parent->getLeftChild() == (*p0)){
			parent->setLeftChild(p1);
		}
		else if(parent->getRightChild() == (*p0)){
			parent->setRightChild(p1);
		}
	}else{
		root = p1;
	}
}

void tree::rightRotation(node **p0){
	cout << "Right rotation on " << (*p0)->getKey() << ".\n";
	node* parent = getParent((*p0)->getKey());
	node *p1=NULL, *p2=NULL;
	p1 = (*p0)->getLeftChild();
	p2 = p1->getRightChild();
	p1->setRightChild(*p0);
	(*p0)->setLeftChild(p2);

	if(parent->isNotNull()){
		if(parent->getLeftChild() == (*p0)){
		parent->setLeftChild(p1);
		}
		else if(parent->getRightChild() == (*p0)){
			parent->setRightChild(p1);
		}
	}else{
		root = p1;
	}
}

node* tree::search(int key){
	node* currentN = root;
	
	if (currentN == NULL)
		return NULL;

	while((currentN->isNotNull()) and (currentN->getKey()!=key)){
		if(key < currentN->getKey())
			currentN = currentN->getLeftChild();
		else
			currentN = currentN->getRightChild();
	}
	if (currentN->isNull())
		return NULL;
	return currentN;
}

void tree::del(node* currentN){
	
	node *parentN = getParent(currentN->getKey());
	node *nChild = new node();

	if(parentN!= NULL)
		if(parentN->getLeftChild() == currentN)
			parentN->setLeftChild(nChild);
		else
			parentN->setRightChild(nChild);

	if(!currentN->isLeaf()){

	}
	currentN->~node();
}

void tree::replace(node* currentN, node* sucessorN){
	
	node* parentN = getParent(currentN->getKey());

	if(currentN == parentN->getLeftChild())
		parentN->setLeftChild(sucessorN);
	else
		parentN->setRightChild(sucessorN);
	
	if (currentN == root){
		root = sucessorN;
	}
	
	if(sucessorN->isNotNull()){
		if(currentN->getLeftChild() != sucessorN)
			sucessorN->setLeftChild(currentN->getLeftChild());
		else sucessorN->setLeftChild(new node());

		if(currentN->getRightChild() != sucessorN)
			sucessorN->setRightChild(currentN->getRightChild());
		else sucessorN->setRightChild(new node());
	}
	currentN->~node();
}	

void tree::insert(int key){
   	
	cout << "Inserting key: " << key << ".\n";
	node *newN = search(key);
	if (newN!=NULL){
		cout << "Error: Node already exist.\n";
		return;
	}
	newN = new node(key);
	
	if (root == NULL){

		root = newN;
	
	}else{

		node* parentN = getParent(key);
		
		if (key > parentN->getKey())
			parentN->setRightChild(newN);
		else
			parentN->setLeftChild(newN);
	}
	printTree();
	cout << "Balancing tree." << endl;
	balance(newN);
	printTree();
}

void tree::balance(node* currentN){
	if (currentN->isNotNull()){
		node* parentN = getParent(currentN->getKey());
		node* uncleN = getUncle(currentN->getKey());
		node* grampaN = getGrampa(currentN->getKey());

		/* CASE 1: NODE IS ROOT: */
		if (currentN == root){
			cout << "Case 1." << endl;
			/* NODE CHANGES TO BLACK */
			currentN->setColor('b');
		}else{
			/* CASE 2: PARENT IS BLACK */
			if (parentN->getColor()=='b'){
				cout << "Case 2." << endl;
				/* DONT TO ANYTHING */
			}
			/* CASE 3: PARENT IS RED */
			else{
				cout << "Case 3.";
				/* CASE 3.1: UNCLE IS RED */
				if (uncleN->getColor()=='r'){
					/* 
						CHANGE PARENT AND UNCLE TO BLACK.
				        CHANGE GRANDFATHER TO RED. 
					*/
					cout << "1.\n";
					parentN->setColor('b');
					uncleN->setColor('b');
					grampaN->setColor('r');
					printTree();
					balance(grampaN);
				}
				/* CASE 3.2: UNCLE IS BLACK */
				else{
					cout << "2.\n";
					/* 
						STEP 1: 
						IF THE INSERTED NODE IS INSIDE GRANDPARENT'S SUBTREE.
				       	ROTATE INSERTED AND PARENT.
					*/
					cout << "Step 1.\n";

					node *temp = NULL;
					int flag = 0;

					if(grampaN->getRightChild() == parentN){
						if(currentN == parentN->getLeftChild()){
							rightRotation(&parentN);
							flag = 1;
						}
					}
					else if(grampaN->getLeftChild() == parentN){
						if(currentN == parentN->getRightChild()){
							leftRotation(&parentN); 
							flag = 1;
						}
					}

					if(flag == 0){
						temp = parentN;
						parentN = currentN;
						currentN = temp;
					}

				    /* STEP 2: ROTATE PARENT AND GRAMPARENT, AND CHANGE COLORS. */
				    cout << "Step 2." << endl;
					grampaN->switchColor();
					if(grampaN->getLeftChild() == currentN){
						rightRotation(&grampaN);
					}else if(grampaN->getRightChild() == currentN){
						leftRotation(&grampaN);
					}
					currentN->switchColor();
				}
			}		
		}
	}		
}

void tree::remove(int key){

	cout << "Removing key: " << key << ".\n";

	node* currentN = search(key);

	if (currentN==NULL){
		cout << "Error: Node not found.\n";
		return;
	}
	
	node* sucessorN = getSucessor(currentN->getKey());
	if(currentN != root){
		node* sublingN = getSibling(currentN->getKey());
	}
	else{
		node* siblingN = new node();
	}
	
	/* STEP 1: STANDARD BST REMOVAL */
	replace(currentN, sucessorN);
	printTree();
	cout << "Balancing tree.\n";

	/* STEP 2: CHECK REMOVED AND SUCESSOR */
	/* CASE 1: IF REMOVED OR SUCESSOR IS RED */
	if(currentN->getColor() == 'r' or sucessorN->getColor() == 'r'){
		cout << "Case 1.\n";
		sucessorN->setColor('b');
		printTree();
	}

	/* CASE 2: IF REMOVED AND SUCESSOR ARE BLACK */
	else if(currentN->getColor() =='b' and sucessorN->getColor()=='b'){
		/* COLOR SUCESSOR AS DOUBLEBLACK */
		cout << "DoubleBlack condition.\n";
		sucessorN->setColor('B'); //Double black
		printTree();
	}
	/* WHILE THE DOUBLEBLACK CONDITION EXISTS */
	while (sucessorN->getColor()=='B'){	
		
		/* CASE 2.1: IF SUCESSOR IS ROOT */
		if (sucessorN == root){
			/* REMOVE DOUBLEBLACK */
			cout << "Case 2.1.\n";
			sucessorN->setColor('b');
		}
		else{
			
			cout << "Case 2.2.";

			node* siblingN = getSibling(sucessorN->getKey());
			node* parentN = getParent(sucessorN->getKey());
			node* leftchildN = siblingN->getLeftChild();
			node* rightchildN = siblingN->getRightChild();
			/* CASE 2.2.a||b: IF SIBLING IS BLACK */
			if (siblingN->getColor()=='b'){
				
				/* CASE 2.2.a: IF AT LEAST ONE CHILDREN IS RED */
				if (leftchildN->getColor()=='r' or rightchildN->getColor()=='r'){
					cout << "a.\n.";
					/* CASE 2.2.a.i: SUCESSOR IS A LEFT CHILD AND REDCHILD IS A LEFT CHILD */
					if (siblingN==parentN->getLeftChild() and leftchildN->getColor()=='r'){
						/* RIGHT ROTATION ON PARENT AND RECOLOR CHILD */
						rightRotation(&parentN);
						leftchildN->switchColor();
					}
					/* CASE 2.2.a.ii: SUCESSOR IS A LEFT CHILD AND REDCHILD IS A RIGHT CHILD */
					else if (siblingN==parentN->getLeftChild() and rightchildN->getColor()=='r'){
						/* DOUBLE RIGHT ROTATION ON PARENT AND RECOLOR CHILD*/
						leftRotation(&siblingN);
						rightRotation(&parentN);
						rightchildN->switchColor();
					}
					/* CASE 2.2.a.iii: SUCESSOR IS A RIGHTCHILD AND REDCHILD IS A RIGHT CHILD */
					if (siblingN==parentN->getRightChild() and rightchildN->getColor()=='r'){
						/* LEFT ROTATION ON PARENT AND RECOLOR CHILD */
						leftRotation(&parentN);
						rightchildN->switchColor();
					}
					/* CASE 2.2.a.iv: SUCESSOR IS A RIGHTCHILD AND REDCHILD IS A LEFT CHILD */
					else if (siblingN==parentN->getRightChild() and leftchildN->getColor()=='r'){
						/* DOUBLE LEFT ROTATION ON PARENT AND RECOLOR CHILD */
						rightRotation(&siblingN);
						leftRotation(&parentN);
						leftchildN->switchColor();
					}
					/* REMOVE DOUBLEBLACK */
					sucessorN->setColor('b');
				}
				/*CASE 2.2.b: BOTH CHILDREN ARE BLACK*/
				else if (leftchildN->getColor()=='b' and rightchildN->getColor()=='b'){
					cout << "b.\n";
					/* RECOLOR SIBLING */
					siblingN->switchColor();
					/* IF PARENT IS RED, RECOLOR AND REMOVE DOUBLEBLACK */
					if (parentN->getColor()=='r'){
						parentN->switchColor();
						sucessorN->setColor('b');
					}
					/* IF PARENT IS BLACK, RECUR TO PARENT */
					else{
						sucessorN->setColor('b');
						sucessorN = parentN;
						sucessorN->setColor('B');
					}
				}
			}
			/* CASE 2.2.c: IF SIBLING IS RED */
			else{
				cout << ".c.\n";
				/* ROTATE SIBLING AND RECOLOR SIBLING AND PARENT */
				if (siblingN==parentN->getLeftChild())
					rightRotation(&parentN);
				else
					leftRotation(&parentN);	
				
				siblingN->switchColor();
				parentN->switchColor();							
			}
		}
		printTree();
	}
}
