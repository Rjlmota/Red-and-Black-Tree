#include <iostream>
#include "tree.h"
using namespace std;

int main(){
  int valor, flag = 0;
  char opcao;
  node* achado;
  tree arv;                              
			
	cout << "legend" << endl;
	cout << "[X] = X is Red" << endl;
	cout << "(X) = X is Black" << endl;		
	
  // Testes Caso 1, 2 e 3.
  arv.insert(10);
    cout << "so far so good\n";
  arv.printTree();

  arv.insert(15);

  arv.printTree();

  arv.insert(5);
  arv.printTree();

  arv.insert(20);
  arv.printTree();  

  /*
	arv.insert(10);
	arv.insert(15);
  arv.insert(5);
  arv.insert(18);
  arv.insert(1);
  arv.insert(3);
  arv.insert(4);

	arv.printTree();	

  //node *toRotate = arv.search(5);

	//arv.leftRotation(&toRotate);
  arv.printTree();
  */
		/*
   	for(;;){                                   
      cout << "\nEscolha uma opcao:\n";
      cout << "1 - Mostrar\n";
      cout << "2 - Inserir\n";
      cout << "3 - Procurar\n";
      cout << "4 - Percorrer\n";
      cout << "5 - Remover\n";
      cout << "6 - Sair\n";
      cin >> opcao;

      switch(opcao){
         case '1':                        
            //arv.mostrararvore();
            break;

         case '2':                        
            cout << "Entre com o valor: ";
            cin >> valor;
            //arv.inserir(valor);
            break;

         case '3':                        
            cout << "Entre com o valor: ";
            cin >> valor;
            achado = arv.search(valor);
            if(achado != NULL)
               cout << "Achado " << valor << "." << endl;
            else
               cout << "Nao achado " << valor << "." << endl;
            break;

         case '4':                        
            //arv.percorrer();
            break;

         case '5':                        
            cout << "Entre com o valor: ";
            cin >> valor;
        
            if(arv.remover(valor))
               cout << "Removido " << valor << "." << endl;
            else
               cout << "Nao achado " << valor << "." << endl;
            
            break;

         case '6': 
             flag = 1;
             break;
             
         default:
            break;
         }  
      if(flag == 1) break;
      }
		*/
   return 0;
}  

