#include <iostream>
#include <cassert>

#include "bst.h"

int main() {
	
	/*
	int value = 4;
	Node <int> n(value);
	Node <int> *n1 = &n;
	*/
	/*
	Node <int> a;
	
	Node <int> n2 (7);
	Node <int> n1 (4);
	
	Node <int> *pn1 = &n1; 
	Node <int> *pn2 = &n2;
	Node <int> n3 (6, pn1, pn2, nullptr);
	
	std::cout<<a.value<<" "<<a.left<<" "<<a.right<<" "<<a.parent<<std::endl;
	
	//std::cout<<pn1->value<<std::endl;
	
	std::cout<<n3.left<<" "<<n3.value<<" "<<n3.right<<" "<<n3.parent<<std::endl;
    */

   

    //SANTO IL SIGNOREEE COSI SI ACCEDE ALLA STRUCT NODE
    Bst<int>::Node n(3);  //nodo indipendente 

    Bst <int> albero1(n); //Costruttore secondario 


    albero1.print();

	
	return 0;
	
	
	
}