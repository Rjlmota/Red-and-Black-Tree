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
		void insert(int key); // Function to insert a node.
		void balance(node* currentN); // Function to check the balance.

		void remove(int key); // Function for removal of node.

		void switchColor(node* currentN); // Function to switch color.
		//SWITCHCOLOR não deveria estar aqui, deve estar no node.h	!!!!


		void leftRotation(node **p);


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
/*
node* tree::search(int key){
	node* currentN = root;
	while(currentN->getKey() != key){
		if(key < currentN->getKey())
			currentN = currentN->leftChild;
		else
			currentN = currentN->rightChild;
		if(currentN == NULL)
			return NULL;
	}
	return currentN;
}
*/

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
            if(temp != NULL){
            	if (temp->getColor() == 'r'){
            		cout << '['<< temp->getKey() << ']';	
							}else{
								cout << '('<< temp->getKey() << ')';
							}
              
              pilhaLocal.push(temp->getLeftChild());
              pilhaLocal.push(temp->getRightChild());

               if(temp->getLeftChild() != NULL || temp->getRightChild() != NULL)
                  linhaVazia = false;
               }
            else
               {
               cout << "--";
               pilhaLocal.push(NULL);
               pilhaLocal.push(NULL);
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

node* tree::search(int key, node*& previousN, char &direction){
   node *currentN;
   if(root){
      currentN = root;
      previousN = currentN;
      while(currentN != NULL){
         int currentNKey;
         currentNKey = currentN->getKey();
         if(currentNKey == key)
            return currentN;

         if(currentNKey < key){
            previousN = currentN;
            direction = 'r';
            currentN = currentN->getRightChild();
         }
         else{
            previousN=currentN;
            direction='l';
            currentN = currentN->getLeftChild();
         }
      }
   }
   return 0;
}

node* tree::getParent(int key){

	node *currentN = root;
	node *previousN = NULL;

	while ((currentN!=NULL) and (currentN->getKey()!=key)){

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

	if (grampaN!=NULL){
		if (grampaN->getRightChild() == parentN)
			return grampaN->getLeftChild();
		else
			return grampaN->getRightChild();
	}
	return NULL;
}

void tree::insert(int key){
   	
	node *newN = new node(key);

	if (root==NULL){
		
		root = newN;
	
	}else{	
	
		node* parentN = getParent(key);
		if (key > parentN->getKey())
			parentN->setRightChild(newN);
		else
			parentN->setLeftChild(newN);
	
	}

	balance(newN);

}

void tree::balance(node* currentN){

	if (currentN != NULL){

		node* parentN = getParent(currentN->getKey());
		node* uncleN = getUncle(currentN->getKey());
		node* grampaN = getGrampa(currentN->getKey());

		/* CASE 1: NODE IS ROOT: */
		if (parentN == NULL){

			/* NODE CHANGES TO BLACK */
			currentN->setColor('b');
		}else{
			/* CASE 2: NODE'S PARENT IS BLACK */
			/* DONT TO ANYTHING */

			/* CASE 3: PARENT AND UNCLE ARE RED. */
			if (parentN->getColor()=='r'){
				if ((uncleN!=NULL) and (uncleN->getColor()=='r')){
					/* 
						CHANGE PARENT AND UNCLE TO BLACK.
				        CHANGE GRANDFATHER TO RED. 
					*/

					parentN->setColor('b');
					uncleN->setColor('b');
					grampaN->setColor('r');
				}
				/* CASE 4: PARENT IS RED AND UNCLE IS BLACK. */	
				if ((uncleN==NULL) or (uncleN->getColor()=='b')){
					/* 
						STEP 1: SE O NO INSERIDO ESTIVER "DENTRO" DA SUBARVORE DO AVÔ:
				       	DO: ROTACIONE O INSERIDO E O PAI.
				    	STEP 2: ROTACIONE O PAI E O AVO E AJUSTE AS CORES. 
					*/
				}
			}		
		}
		// TEM QUE FICAR DE OLHO NESSE CASO 4 
		// PQ ACHO QUE VAI TER QUE MUDAR
		// QUAL NODE É ENVIADO PRA RECURSIVIDADE.
		balance(grampaN);

	}		
}

void tree::remove(int key){
   //Adapt to RBT.
}