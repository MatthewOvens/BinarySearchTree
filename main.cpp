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

struct equal_double {
	bool operator()(double a, double b) const {
		return a==b;
	}
};

struct compare_double {
	bool operator()(double a, double b) const {
		return a<b;
	}
};

struct equal_char {
	bool operator()(char a, char b) const {
		return a==b;
	}
};

struct compare_char {
	bool operator()(char a, char b) const {
		return a<b;
	}
};

struct equal_string {
	bool operator()(char *a, char *b) const {

		unsigned int contA = 0;
		unsigned int contB = 0;

		for(int i = 0; a[i] != '\0'; i++){
			contA++;
		}
		for(int i = 0; b[i] != '\0'; i++){
			contB++;
		}

		if(contA == contB){

			for(int i = 0; i<contA; i++){
				if(a[i] != b[i]){
					return false;
				}
			}
			return true;
		}
		else 
			return false;
	}
};

struct compare_string {
	bool operator()(char *a, char *b) const {





		//sgkusgkuhsdg
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


   //TEST COSTRUTTORE SECONDARIO CON ARRAY DIN INTERI 
	const int dim = 12;
	int a[dim]= {10, 5, 15, 3, 8, 20, 1, 4, 6, 9, 18, 22};
	Bst<int, compare_int, equal_int> albero2(a, dim);

	std::cout<<"Stampa di albero2 : "<<std::endl;
	albero2.printTree(albero2.get_head());
	std::cout<<"Elementi al suo interno : "<<albero2.get_size()<<std::endl;


   	//TEST ADD 
    Bst<int, compare_int, equal_int> albero1;  //Costruttore di default 

	albero1.add(15);
	albero1.add(10);
	albero1.add(6);
	albero1.add(18);
	albero1.add(20);
	albero1.add(16);
	albero1.add(13);

	std::cout<<"Stampa di albero1 : "<<std::endl;
	albero1.printTree(albero1.get_head());
	std::cout<<"Elementi al suo interno : "<<albero1.get_size()<<std::endl;


	//TEST COPY COSTRUCTOR 
	Bst<int, compare_int, equal_int> albero3(albero1);

	std::cout<<"Stampa di albero3 : "<<std::endl;
	albero3.printTree(albero3.get_head());
	std::cout<<"Elementi al suo interno : "<<albero3.get_size()<<std::endl;


	//TEST CLEAR E DISTRUTTORI

	//albero1.clear();
	albero2.clear();
	albero3.clear();
	
	std::cout<<"Dimensione albero1 dopo clear: "<<albero1.get_size()<<std::endl;
	std::cout<<"Dimensione albero2 dopo clear: "<<albero2.get_size()<<std::endl;
	std::cout<<"Dimensione albero3 dopo clear: "<<albero3.get_size()<<std::endl;



	//TEST OPERATORE DI ASSEGNAMENTO 
	Bst<int, compare_int, equal_int> albero4;

	albero4 = albero1;

	albero4.printTree(albero4.get_head());





	
	/*
	bool b = ('f'=='f');

	std::cout<<b<<std::endl;
	*/


	//TEST ITERATORI 
	
	


    //Bst <int, int , int> albero1(n); //Niente costruttore con un solo nodo 


	//TEST METODI FINDMIN E FINDMAX

   
	








	return 0;
}