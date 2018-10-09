#include <stack>
#include "node.h"
using namespace std;

//FIXME LEFTROTATION
//ADDME RIGHT ROTATION



class tree {
	private:  
		node* root;

	public:

		tree(); //Constructor

		~tree(); //Destructor

		void printTree(); // Function to print tree.
		void eraseData(node *localRoot); // Function used by destructor.
		node* search(int key); // Function to search for node.
		node* search(int key, node*& previousN, char &direction); // Used by removal method.
		node* getParent(int key); // Function used to get the node's parent.
		node* getGrampa(int key); // Function used to get the node grampa.
		node* getUncle(int key); // Function used to get the node uncle.
		node* getSibling(int key); // Function used to get the node sibling.
		//node* getSucessor(node* currentN); // Function to get a sucessor of a node.
		void insert(int key); // Function to insert a node.
		void balance(node* currentN); // Function to check the balance.

		void remove(int key); // Function for removal of node.

		void switchColor(node* currentN); // Function to switch color.
		//SWITCHCOLOR não deveria estar aqui, deve estar no node.h	!!!!


		void leftRotation(node **p); // Function to do a left rotation on a tree.
		void rightRotation(node **p); // Function to do a right rotation on a tree.
		void del(node *p);
		void replace(node* currentN, node* sucessorN);

};	


tree::tree(){
	root = NULL;
}

tree::~tree(){
	eraseData(root);
}

void tree::eraseData(node* localRoot){
	//Adapt to RBT.
}

node* tree::search(int key){
	node* currentN = root;
	while((currentN->isNotNull()) and (currentN->getKey()!=key)){

		if(key < currentN->getKey())
			currentN = currentN->getLeftChild();
		else
			currentN = currentN->getRightChild();
	}
	return currentN;
}

void tree::leftRotation(node **p0){
	cout << "Left rotation on " << (*p0)->getKey() << endl;
	node* parent = getParent((*p0)->getKey());
	node *p1=NULL, *p2=NULL;
	p1 = (*p0)->getRightChild();
	p2 = p1->getLeftChild();
	p1->setLeftChild(*p0);
	(*p0)->setRightChild(p2);

	if(parent != NULL){
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
	cout << "Right rotation on " << (*p0)->getKey() << endl;
	node* parent = getParent((*p0)->getKey());
	node *p1=NULL, *p2=NULL;
	p1 = (*p0)->getLeftChild();
	p2 = p1->getRightChild();
	p1->setRightChild(*p0);
	(*p0)->setLeftChild(p2);

	if(parent != NULL){
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

void tree::switchColor(node *currentN){
	if(currentN->getColor() == 'r'){
		currentN->setColor('b');
	}else{
		currentN->setColor('r');
	}
}

void tree::printTree(){

      stack<node*> pilhaGlobal;
      pilhaGlobal.push(root);
      int nVazios = 32;
      bool linhaVazia = false;

      cout << endl;
      while(linhaVazia==false)
         {
         stack<node*> pilhaLocal;
         linhaVazia = true;

         for(int j=0; j<nVazios; j++)
            cout << ' ';

         while(pilhaGlobal.empty()==false)
            {
            node* temp = pilhaGlobal.top();
            pilhaGlobal.pop();
            if(temp->isNotNull()){
            	if (temp->getColor() == 'r'){
            		cout << '['<< temp->getKey() << ']';	
							}else{
								cout << '('<< temp->getKey() << ')';
							}
              
              pilhaLocal.push(temp->getLeftChild());
              pilhaLocal.push(temp->getRightChild());

               if(temp->getLeftChild()->isNotNull() || temp->getRightChild()->isNotNull())
                  linhaVazia = false;
               }
            else
               {
               cout << "--";
               node *nullNode = new node();
               pilhaLocal.push(nullNode);
               pilhaLocal.push(nullNode);
               }
            for(int j=0; j<nVazios*2-2; j++)
               cout << ' ';
            }  
         cout << endl;
         nVazios = nVazios/2;
         while(pilhaLocal.empty()==false)
            {
            pilhaGlobal.push( pilhaLocal.top() );
            pilhaLocal.pop();
            }
         }  

      cout << endl;
}  

node* tree::getParent(int key){

	node *currentN = root;
	node *previousN = NULL;
	while ((currentN->isNotNull()) and (currentN->getKey()!=key)){
		previousN = currentN;
		if(key > currentN->getKey())
			currentN = currentN->getRightChild();
		else if(key < currentN->getKey())
			currentN = currentN->getLeftChild();
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

/*
node* tree::getSucessor(int key){
	node* currentN = search(key);
	node* sucessorN = currentN->getLeftChild();
	if (sucessorN->isNotNull()){
		while (sucessorN->getRightChild()->isNotNull())
			sucessorN = sucessorN->getRightChild();
	}
	return sucessorN;
}
*/
void tree::insert(int key){
   	
	node *newN = new node(key);

	if (root == NULL){
		
		root = newN;
	
	}else{	
	
		node* parentN = getParent(key);
		if (key > parentN->getKey())
			parentN->setRightChild(newN);
		else{
			parentN->setLeftChild(newN);
		}
	
	}
	cout << "Insert key: " << key << endl;
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
		if (parentN == NULL){
			cout << "Case 1." << endl;
			/* NODE CHANGES TO BLACK */
			currentN->setColor('b');
		}else{
			/* CASE 2: NODE'S PARENT IS BLACK */
			if (parentN->getColor()=='b'){
				cout << "Case 2." << endl;
				/* DONT TO ANYTHING */
			}
			/* CASE 3: PARENT AND UNCLE ARE RED. */
			else if (parentN->getColor()=='r'){
				if ((uncleN->isNotNull()) and (uncleN->getColor()=='r')){
					/* 
						CHANGE PARENT AND UNCLE TO BLACK.
				        CHANGE GRANDFATHER TO RED. 
					*/
					cout << "Case 3." << endl;
					parentN->setColor('b');
					uncleN->setColor('b');
					grampaN->setColor('r');
					balance(grampaN);
					
				} else if ((uncleN->isNull()) or (uncleN->getColor()=='b')){
					/* CASE 4: PARENT IS RED AND UNCLE IS BLACK. */	
					/* 
						STEP 1: IF THE INSERTED NODE IS INSIDE GRANDPARENT'S SUBTREE.
				       	DO: ROTATE INSERTED AND PARENT.
		
					*/
					cout << "Case 4." << endl;
					cout << "Step 1." << endl;

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

				    //STEP 2: ROTATE PARENT AND GRAMPARENT, AND CHANGE COLORS.
				    cout << "Step 2." << endl;
					switchColor(grampaN);
					if(grampaN->getLeftChild() == currentN){
						rightRotation(&grampaN);
					}else if(grampaN->getRightChild() == currentN){
						leftRotation(&grampaN);
					}

					switchColor(currentN);

				}
			}		
		}
	}		
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
	/*
	node* parent = getParent(currentN->getKey());

	if(currentN == parentN->getLeftChild())
		parentN->setLeftChild(sucessorN);
	else
		parentN->setRightChild(sucessorN);
		*/

}

void delete_one_child(node* currentN){
	/*
	node* child = isLeaf(currentN->getRightChild()) ? currentN->getLeftChild() : currentN->getRightChild();
	replace_node(currentN, child);
	if(currentN->getColor() == 'b'){
		if(child->getColor() == 'r')
			child->setColor('b');
		else
			//delete_case1(child);
	}
	currentN->~node();
	*/
}		

void tree::remove(int key){
	//Adapt to RBT
	//node* currentN = search(key);
	//node* sucessorN = getSucessor(currentN->getKey());
	/*
	// ESSE REPLACE TEM QUE CONSEGUIR FUNCIONAR PRA NULL TBM.
	// EU ACHO QUE A ORDEM DE QUANDO DAR REPLACE E REMOVE AINDA TÁ ERRADA.
	//replace(currentN, sucessorN);
	//remove(sucessorN);
	
	int doubleblack = true;

	while (doubleblack){
		// IF CURRENTN IS ROOT.
		if (currentN==root){
			doubleblack = false;
		}
		// IF CURRENTN OR SUCESSORN IS RED.
		else if ((currentN->getColor()=='r') or ((sucessorN->isNotNull()) and (sucessorN->getColor()=='r'))){			
			//currentN->setColor('b');
			//doubleblack = false;
		}
		// IF BOTH CURRENTN AND SUCESSORN ARE BLACK.
		else{

			node* siblingN = getSibling(currentN->getKey());
			node* parentN = getParent(currentN->getKey());

			// IF SIBLINGN IS BLACK.
			if (siblingN->getColor()=='b'){

				node* leftchildN = siblingN->getLeftChild();
				node* righchildN = siblingN->getRightChild();
				
				// BOTH CHILDREN ARE BLACK.
				if ((leftchildN->isNull() or leftchildN->getColor()=='b') and (rightchildN->isNull() or righchildN->getColor()=='b')){
					// switchCOlor(siblingN);
					if (parentN->getColor()=='b'){
						//RECUR TO PARENT.
						//currentN = parentN;
					}else{
						//switchColor(parentN);
						//doubleblack = false;
					}
				}
				// AT LEAST ONE OF IT'S CHILDREN IS RED.
				// RED IS LEFT CHILD OF SIBLINGN.
				else if ((leftchildN!=NULL) and (leftchildN->getColor()=='r')){
					// SIBLINGN IS LEFT CHILD OF PARENTN.
					if (siblingN==parentN->getLeftChild()){
						// LEFT ROTATION ON SIBLINGN.
						//doubleblack = false;
					}
					// SIBLING IS RIGHT CHILD OF PARENTN.
					if (siblingN==parentN->getRightChild()){
						// DOUBLE LEFT ROTATION ON SIBLINGN.
						//doubleblack = false;
					}
				// RED IS RIGHT CHILD OF SIBLINGN.
				}else if ((righchildN!=NULL) and (righchildN->getColor()=='r')){
					// SIBLINGN IS LEFT CHILD OF PARENTN.
					if (siblingN == parentN->getLeftChild()){
						// DOUBLE RIGHT ROTATION ON SIBLINGN.
						//doubleblack = false;
					}
					// SIBLING IS RIGHT CHILD OF PARENTN.
					if (siblingN -- parentN->getRightChild()){
						// RIGHT ROTATION ON SIBLINGN.
						//doubleblack = false;
					}
				}
			}
			// IF SIBLINGN IS RED.
			else if (siblingN->getColor()=='r'){
				// SIBLINGN IS LEFT CHILD OF PARENT
				if (siblingN==parentN->getLeftChild()){
					// RIGHT ROTATION ON SIBLINGN.
				}
				// SIBLINGN IS RIGHT CHILD OF PARENT
				else{
					// LEFT ROTATION ON SIBLINGN.
				}
				//switchColor(siblingN);
				//switchColor(parentN);
				// AQUI A GENTE TA FERRADO, PQ ELE FAZ A CHECAGEM DE DOUBLEBLACK EM UM NULO. !!!
				//currentN = sucessorN;
			}
		}
	//sucessorN = getSucessor(currentN->getKey());
	}
	*/
}


