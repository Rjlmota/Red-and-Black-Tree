#include <iostream>
#include "tree.h"
#include <unistd.h>
using namespace std;

int main(){
  int valor, flag = 0;
  char opcao;
  node* aux1;
  node* aux2;
  tree arv;                              
	
  cout << "legend" << endl;
  cout << "[X] = X is Red" << endl;
  cout << "(X) = X is Black" << endl << endl; 

  arv.insert(20);
  //arv.printTree();

  arv.insert(10);
  //cout << "aaa" << endl;
  //arv.printTree();
  arv.insert(30);
  arv.insert(5);
  //arv.printTree();
  //cout << "oi2" << arv.search(100)->getLeftChild() << endl;
  //arv.insert(50);
  arv.remove(5);
  arv.remove(10);
  //arv.remove(40);
  //arv.printTree();
  //arv.printTree();
  //aux1 = arv.search(75);
  //aux2 = arv.getSucessor(aux1);
  //cout << aux2->getKey() << endl;

  //cout << arv.search(65)->getLeftChild()->getKey() << endl;
  /*	
  int temp;
  
  int entrada = 0;
  while(true){
    
    cout << "30 50 20 10 15" << endl;
    cout << ">>";

    cin >> entrada;
    if(entrada == -1)
      return 0;
    arv.insert(entrada);
    achado = arv.search(entrada);
    cout << achado->getKey() << endl;

    //Habilite esse cin pra evitar o loop infinito
    cin >> temp;
    
    arv.printTree();
    }
  */
  /*

    arv.insert(30);
    arv.insert(20);
    arv.insert(50);
    arv.printTree();
    cout << "adding 10" << endl;
    arv.insert(10);
    arv.printTree();
    cout << "adding 5" << endl;
    arv.insert(5);
    //arv.printTree();
   */
    /*
    arv.printTree();
    arv.insert(25);
    arv.insert(45);
    arv.insert(60);
    arv.printTree();
    arv.insert(5);
    arv.insert(15);
    usleep(1000);
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

