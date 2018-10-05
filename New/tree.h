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
		node* search(int key, node*& previousN, char &direction); // Used by removal method.
		void insert(int key); // Function to insert a node.
		//void goThrough(); // Function to run through the tree.
		//void upper(node* localRoot); // Function used to run through the tree.
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
void tree::insert(int key){
	//Adapt to RBT.
   /* CASE 1: NODE IS ROOT: */
	if (root==NULL){
		node *newN = new node(key);
		
		/* DO: INSERTED NODE CHANGES TO BLACK */
		root = newN;
		switchColor(root);
	
	}else{	
		
		node* currentN = root;
		node* parentN = NULL;

		while(currentN!=NULL){
			parentN = currentN;
			if (key > currentN->getKey())
				currentN = currentN->getRightChild();
			else
				currentN = currentN->getLeftChild();
		}

		node* grampaN = getGrampa(parentN->getKey());
		node* uncleN = getUncle(parentN);

		char pColor = parentN->getColor();
		char uColor = 'b';

		if(uncleN != NULL){
			uColor = uncleN->getColor();
		}
	   	/* CASE 2: NODE'S PARENT IS BLACK */
		if (pColor == 'b'){
			
			/* DONT TO ANYTHING */
			insert_case2(parentN, key);
		}

   		/* CASE 3: PARENT AND UNCLE ARE RED. */
		else if ((pColor == 'r') and (uColor == 'r')){
		
			/* 
			DO: CHANGE PARENT AND UNCLE TO BLACK.
        	CHANGE GRANDFATHER TO RED. 
			*/
			insert_case3(parentN, uncleN, key);
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

void tree::switchColor(node *currentN){
	if(currentN->getColor() == 'r'){
		currentN->setColor('b');
	}else{
		currentN->setColor('r');
	}
}
/*
void tree::goThrough(){
	upper(root);
}
*/
/*
void tree::upper(node* localRoot){
	if(localRoot != NULL){
		upper(localRoot->leftChild);
		cout << localRoot->getKey() << " ";
		upper(localRoot->rightChild);

	}
}
*/

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


void tree::remove(int key){
   //Adapt to RBT.
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

node* tree::getUncle(node* parentN){

	node* grampaN = getParent(parentN->getKey());
	
	node* uncleN = NULL;
	if(grampaN != NULL){
		if(grampaN->getLeftChild() != NULL and grampaN->getRightChild() != NULL){
			if(grampaN->getLeftChild()->getKey() == parentN->getKey())
				uncleN = grampaN->getRightChild();
			else
				uncleN = grampaN->getLeftChild();
		}
	}
	return uncleN;
}

node* tree::getGrampa(int key){

	node* parentN = getParent(key);

	if(parentN != NULL)
		return getParent(parentN->getKey());

	return NULL;

}



node* tree::getParent(int key){
	node *currentN = root;
	node *previousN = root;

	/* Uma alternativa para getParent(). Pode ser usada para achar o pai do node a ser inserido.

	node *previousN = NULL;
	if (currentN!=NULL){
		while(currentN->getKey()!=key){
			previousN = currentN;
			if(key > currentN->getKey())
				currentN = currentN->getRightChild();
			else if(key < currentN->getKey())
				currentN = currentN->getLeftChild();
		}
	}

	return previousN
	*/

	if(currentN->getKey() == key)
		return NULL;

	else{
		while(currentN != NULL){

			if(key == currentN->getKey())
				return previousN;

			previousN = currentN;
			if(key > currentN->getKey())
				currentN = currentN->getRightChild();
			else if(key < currentN->getKey())
				currentN = currentN->getLeftChild();

		}

	}
	return currentN;
}


void tree::insert_case2(node* parentN, int key){
	node* newN = new node(key);
	if (key > parentN->getKey()){
		parentN->setRightChild(newN);
	}else{
		parentN->setLeftChild(newN);
	}
}

void tree::insert_case3(node *parentN, node* uncleN, int key){
		/* 
		DO: CHANGE PARENT AND UNCLE TO BLACK.
        CHANGE GRANDFATHER TO RED. 
		*/
		uncleN->setColor('b');
		parentN->setColor('b');
		node* grampaN = getParent(parentN->getKey());
		if(grampaN != root){
			grampaN->setColor('r');
		}
		insert_case2(parentN, key);

}

