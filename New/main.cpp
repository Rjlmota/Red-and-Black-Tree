#include <iostream>
#include "tree.h"
#include <unistd.h>
using namespace std;

int main(){

  tree arv;                              
	
  cout << "legend" << endl;
  cout << "[X] = X is Red" << endl;
  cout << "(X) = X is Black" << endl << endl; 

  arv.insert(20);
  arv.insert(10);
  arv.insert(30);
  arv.insert(5);
  arv.remove(5);
  arv.remove(10);

   return 0;
}  

