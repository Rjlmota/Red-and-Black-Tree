#include <iostream>
#include <stdio.h>
#include "tree.h"
//#include <unistd.h>
using namespace std;

int main(){

  tree arv;                              

  int option = 0;
  int key;
  while(option != 5){
    printf("\n1. Insert node.\n2. Remove node.\n3. Search node.\n4. Show tree.\n5. Quit.\n:>");
    scanf("%i", &option);
    
    if (option==5){
      //DO NOTHING
    }else if (option==4){
      arv.printTree();
    }else if (option>=1 and option<=3){
        printf("Key:>");
        scanf("%i", &key);
        if (option==1){
          arv.insert(key);
        }else if (option==2){
          arv.remove(key);
        }else{
          arv.search(key);
        }
    }else{
      printf("Option does not exist");
    }
  }
  return 0;
}  

