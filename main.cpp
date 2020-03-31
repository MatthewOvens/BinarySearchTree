#include <iostream>
#include <cassert>

#include "bst.h"


 
struct equal_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

struct compare_int {
	bool operator()(int a, int b) const {
		return a<b;
	}
};



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
	

	//TEST COSTRUTTORE SECONDARIO NODO 
	Node <int> *pn1 = &n1; 
	Node <int> *pn2 = &n2;
	Node <int> n3 (6, pn1, pn2, nullptr);
	
	std::cout<<a.value<<" "<<a.left<<" "<<a.right<<" "<<a.parent<<std::endl;
	
	//std::cout<<pn1->value<<std::endl;
	
	std::cout<<n3.left<<" "<<n3.value<<" "<<n3.right<<" "<<n3.parent<<std::endl;
    */


   //TEST COSTRUTTORE SECONDARIO CON ARRAY 
	int dim = 10;
	int a[dim]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	Bst<int, compare_int, equal_int> albero2(a, dim);

	albero2.print();


   	//TEST ADD 
    Bst<int, compare_int, equal_int> albero1;  //Costruttore di default 

	albero1.add(4);
	albero1.print();

	albero1.add(1);
	albero1.print();

	albero1.add(6);
	albero1.print();

	albero1.add(10);
	albero1.print();

	albero1.add(3);

	 albero1.print();


	//TEST ITERATORI 
	
	


    //Bst <int, int , int> albero1(n); //Niente costruttore con un solo nodo 


	//TEST METODI FINDMIN E FINDMAX

   
	








	return 0;
}