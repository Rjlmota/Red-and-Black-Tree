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

		
		node* getParent(int key); // Function used to get the node's parent.
		node* getUncle(node* parent); // Function used to get the node uncle.
		node* getGrampa(int key); // Function used to get the node grampa.
		void eraseData(node *localRoot); // Function used by destructor.
		node* search(int key); // Function to search for node.
		node* search(int key, node*& previous, char &direction); // Used by removal method.
		void insert(int key); // Function to insert a node.
		void goThrough(); // Function to run through the tree.
		void upper(node* localRoot); // Function used to run through the tree.
		void remove(int key); // Function for removal of node.
		void printTree(); // Function to print tree.
		void insert_case1(node* parent, int key); //bla
		void insert_case2(node* parent, int key); // Function to add a node for case 2.
		void insert_case3(node*parent, node* uncle, int key);
		void switchColor(node* p); // Function to switch color
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
		node *p = new node(key);
		
		/* DO: INSERTED NODE CHANGES TO BLACK */
		root = p;
		switchColor(root);
	
	}else{	
		
		node* current = root;
		node* parent = NULL;
		while(current!=NULL){
			parent = current;
			if (key > current->getKey()){
				current = current->getRightChild();
			}else{
				current = current->getLeftChild();
			}
		}
		

		//UNCLE
		node* grampa = getParent(parent->key);
		
		node* uncle = NULL;

		uncle = getUncle(parent);
		char pColor = parent->getColor();
		char uColor = '.';

		if(uncle != NULL){
			uColor = uncle->getColor();
		}
	   	/* CASE 2: NODE'S PARENT IS BLACK */
		if (pColor == 'b'){
			
			/* DONT TO ANYTHING */
			insert_case2(parent, key);
		}

   		/* CASE 3: PARENT AND UNCLE ARE RED. */
		else if ((pColor == 'r')&&(uColor == 'r')){
		
			/* 
			DO: CHANGE PARENT AND UNCLE TO BLACK.
        	CHANGE GRANDFATHER TO RED. 
			*/
			insert_case3(parent, uncle, key);
		}
		
		/* CASE 4: FATHER IS RED AND UNCLE IS BLACK. */
		//else if((pColor == 'r')&&(uColor == 'b')){
			
			/* 
			STEP 1: SE O NO INSERIDO ESTIVER "DENTRO" DA SUBARVORE DO AVÔ:
        	DO: ROTACIONE O INSERIDO E O PAI.
      STEP 2: ROTACIONE O PAI E O AVO E AJUSTE AS CORES. 
			*/
			
			//insert_case4(key);
		//}

		
		/* ERRO! */
		else{
			
			cout << pColor << endl;
			cout << uColor << endl;
			cout << "ERRO 404: CASE NOT FOUND!\n" ; 
			
		}
		
	}



}

void tree::leftRotation(node **p0){
  node *p1=NULL, *p2=NULL;
  p1 = (*p0)->getRightChild();
  p2 = p1->getLeftChild();
  p1->setLeftChild(*p0);
  (*p0)->setRightChild(p2);
  //(*p0)->fb = 0;
  //p1->fb = 0;
  (*p0) = p1;
}

void tree::switchColor(node *p){
	if(p->getColor() == 'r'){
		p->color = 'b';
	}else{
		p->color = 'r';
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
            if(temp != NULL){
            	if (temp->getColor() == 'r'){
            		cout << '['<< temp->getKey() << ']';	
							}else{
								cout << '('<< temp->getKey() << ')';
							}
              
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

node* tree::getUncle(node* parent){


	node* grampa = getParent(parent->getKey());
	
	
	node* uncle = NULL;
	if(grampa != NULL){
		if(grampa->getLeftChild() != NULL and grampa->getRightChild() != NULL){
			if(grampa->getLeftChild()->key == parent->getKey())
				uncle = grampa->getRightChild();
			else
				uncle = grampa->getLeftChild();
		}
	}
	return uncle;
}

node* tree::getGrampa(int key){
	node* grampa = NULL;
	node* parent = getParent(key);
	if(parent != NULL)
		grampa = getParent(parent->key);
	
	return grampa;

}



node* tree::getParent(int key){
	node *p = root;
	node *previous = root;
	if(root->key == key)
		return NULL;
	else{
		while(p != NULL){

			if(key == p->key)
				return previous;

			previous = p;
			if(key > p->key)
				p = p->getRightChild();
			else if(key < p->key)
				p = p->getLeftChild();

		}

	}
}


void tree::insert_case2(node* parent, int key){
	node* newNode = new node(key);
	if (key > parent->getKey()){
		parent->setRightChild(newNode); // Aquele loop infinito era pq tinha um "parent" em vez de "newNode" aqui haah.
	}else{
		parent->setLeftChild(newNode);
	}
}

void tree::insert_case3(node *parent, node* uncle, int key){
		/* 
		DO: CHANGE PARENT AND UNCLE TO BLACK.
        CHANGE GRANDFATHER TO RED. 
		*/
		uncle->setColor('b');
		parent->setColor('b');
		node* grampa = getParent(parent->key);
		if(grampa != root){
			grampa->setColor('r');
		}
		insert_case2(parent, key);

}

