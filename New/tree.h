#include <stack>
#include "node.h"
using namespace std;


class tree {
	private:  
		node* root;

	public:

		tree(); //Constructor

		~tree(); //Destructor

		node* getUncle(int key); // Function used to get the node uncle.
		node* getGrampa(int key); // Function used to get the node grampa.
		void eraseData(node *localRoot); // Function used by destructor.
		node* search(int key); // Function to search for node.
		node* search(int key, node*& previous, char &direction); // Used by removal method.
		void insert(int key); // Function to insert a node.
		void goThrough(); // Function to run through the tree.
		void upper(node* localRoot); // Function used to run through the tree.
		void remove(int key); // Function for removal of node.
		void printTree(); // Function to print tree.

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
	node* currentP = root;
	while(currentP->getKey() != key){
		if(key < currentP->getKey())
			currentP = currentP->leftChild;
		else
			currentP = currentP->rightChild;
		if(currentP == NULL)
			return NULL;
	}
	return currentP;
}

void tree::insert(int key){
	//Adapt to RBT.
	
   /* CASE 1: NODE IS ROOT: */
	if (root==NULL){
		
		/* DO: INSERTED NODE CHANGES TO BLACK */
		//insert_case1(key);
	
	}else{
		
		node* current = root;
		node* parent = NULL;
		
		while(current!=NULL){
			parent = current;
			if (key > current->getKey())
				current = current->getRightChild();
			else
				current = current->getLeftChild();
		}
		
		node* uncle = getUncle(parent->getKey());
		char pColor = parent->getColor();
		char uColor = uncle->getColor();
		
	   	/* CASE 2: NODE'S PARENT IS BLACK */
		if (pColor == 'b'){
			
			/* DONT TO ANYTHING */
			//insert_case2(key);
		}

   		/* CASE 3: PARENT AND UNCLE ARE RED. */
		else if ((pColor == 'r')&&(uColor == 'r')){
		
			/* 
			DO: CHANGE PARENT AND UNCLE TO BLACK.
        	CHANGE GRANDFATHER TO RED. 
			*/
			//insert_case3(key);
		}
		
		/* CASE 4: FATHER IS RED AND UNCLE IS BLACK. */
		else if((pColor == 'r')&&(uColor == 'b')){
			
			/* 
			STEP 1: SE O NO INSERIDO ESTIVER "DENTRO" DA SUBARVORE DO AVÔ:
        	DO: ROTACIONE O INSERIDO E O PAI.
      		STEP 2: ROTACIONE O PAI E O AVO E AJUSTE AS CORES. 
			*/
			
			//insert_case4(key);
		}
		
		/* ERRO! */
		else{
			
			cout << "ERRO 404: CASE NOT FOUND!\n" ; 
			
		}
		
	}



}

void tree::goThrough(){
	upper(root);
}

void tree::upper(node* localRoot){
	if(localRoot != NULL){
		upper(localRoot->leftChild);
		cout << localRoot->getKey() << " ";
		upper(localRoot->rightChild);

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
            if(temp != NULL)
               {
               cout << temp->getKey();
               pilhaLocal.push(temp->leftChild);
               pilhaLocal.push(temp->rightChild);

               if(temp->leftChild != NULL || temp->rightChild != NULL)
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


void tree::remove(int key){
   //Adapt to RBT.
}

node* tree::search(int key, node*& previous, char &direction){
   node *currentP;
   if(root){
      currentP = root;
      previous = currentP;
      while(currentP != NULL){
         int currentPKey;
         currentPKey = currentP->getKey();
         if(currentPKey == key)
            return currentP;

         if(currentPKey < key){
            previous = currentP;
            direction = 'r';
            currentP = currentP->getRightChild();
         }
         else{
            previous=currentP;
            direction='l';
            currentP = currentP->getLeftChild();
         }
      }
   }
   return 0;
}

node* tree::getUncle(int key){
	// KEY = PARENT->KEY.
	node* currentP = root;
	while(currentP != NULL){
		if (currentP->leftChild->getKey() == key){
			return currentP->getRightChild();
		}
		else if (currentP->rightChild->getKey()== key){
			return currentP->getLeftChild();
		}
		else{
			if (key > currentP->getKey()){
				currentP = currentP->getRightChild();
			}else{
				currentP = currentP->getLeftChild();
			}
		}
	}
	return currentP;
}

node* tree::getGrampa(int key){
	// KEY = PARENT->KEY.
	node* currentP = root;
	while(currentP != NULL){
		if (currentP->getLeftChild()->getKey() == key){
			return currentP;
		}
		else if (currentP->getRightChild()->getKey()== key){
			return currentP;
		}
		else{
			if (key > currentP->getKey()){
				currentP = currentP->getRightChild();
			}else{
				currentP = currentP->getLeftChild();
			}
		}
	}
	return currentP;
}
