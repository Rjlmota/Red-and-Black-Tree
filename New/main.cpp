#include <iostream>
#include "tree.h"
//#include <unistd.h>
using namespace std;

int main(){

  tree arv;                              

  int option = 0;
  int key;
  node *n = NULL;
  while(option != 5){
    cout << "\n1. Insert node.\n2. Remove node.\n3. Search node.\n4. Show tree.\n5. Quit.\n:>";
    cin >> option;
    
    if (option==5){
      //DO NOTHING
    }else if (option==4){
      arv.printTree();
    }else if (option>=1 and option<=3){
        cout <<"Key:>";
        cin >> key;
        if (option==1){
          arv.insert(key);
        }else if (option==2){
          arv.remove(key);
        }else{
          n = arv.search(key);
          if (n==NULL){
            cout << "Error: Node not found.\n";
          }else{
            cout << "Node:" << n << "\nKey: " << n->getKey() << "\nColor: " << n->getColor() << "\n";
          }
        }
    }else{
      cout << "Option does not exist\n";
    }
  }

  return 0;
}  

