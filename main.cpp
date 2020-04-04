#include <iostream>
#include <cassert>
#include "bst.h"


/**
	@brief Funtore per il confronto tra tipi int.
	
	Funtore per l'uguaglianza tra tipi int.
*/
struct equal_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

/**
	@brief Funtore per il confronto tra tipi int.
	
	Funtore per il confronto tra tipi int. 
*/
struct compare_int {
	bool operator()(int a, int b) const {
		return a<b;
	}
};

/**
	@brief Funtore per il confronto tra tipi char.
	
	Funtore per l'uguaglianza tra tipi char.
*/
struct equal_char {
	bool operator()(char a, char b) const {
		return a==b;
	}
};

/**
   	@brief Funtore per il confronto tra tipi char.

	Ritorna un booleano, true se 'a' è minore di 'b', secondo l'ordine standard dei dati di tipo char,
	false in caso contrario  
*/
struct compare_char {
	bool operator()(char a, char b) const {
		return a<b;
	}
};

/**
	@brief Funtore per il confronto tra stringhe.
	
	Funtore per l'uguaglianza tra stringhe.
*/
struct equal_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return (a==b);
	} 
};

/**
	@brief Funtore per il confronto tra stringhe.
	
	Funtore per il confronto tra stringhe. Si basa sulla lunghezza
	delle stringhe, ritorna true se la prima stringa (a) e' piu' corta
	della seconda (b). 
*/
struct compare_string {
	bool operator()(const std::string &a, const std::string &b) const {
		return (a.size()<b.size());
	} 
};

/**
	Struct Book che implementa un libro.

	@brief Struct Book che implementa un libro.
*/
struct Book {

	int codice;
	int numero_pagine;	

	Book (int c, int np) : codice(c), numero_pagine(np) {}
};

/**
	@brief Funtore per il confronto di due libri.
	
	Funtore per il confronto di due libri. 
	Si basa sul numero di pagine, ritorna true se il primo libro ha meno pagine del secondo
*/
struct compare_books {
	bool operator()(const Book &l1, const Book &l2) const {
		return (l1.numero_pagine < l2.numero_pagine);
	} 
};

/**
	@brief Funtore per il confronto di due libri.
	
	Funtore per il confronto di uguaglianza tra due libri. 
	Ritorna true se l1.codice == l2.codice 
*/
struct equal_books {
	bool operator()(const Book &l1, const Book &l2) const {
		return (l1.codice==l2.codice);
	} 
};

/**
	Ridefinizione dell'operatore di stream << per un libro.
	Necessario per l'operatore di stream della classe Bst.
*/
std::ostream &operator<<(std::ostream &os, const Book &p) {
	std::cout<<"[Code: "<<p.codice<<"/Pages: "<<p.numero_pagine<<"]";
	return os;
}

/**
	@brief Funtore di controllo.
	
	Funtore da pasare al printIf come predicato P
	Controlla se il valore passatogli come parametro è pari
	Ritorna true se è pari, false in caso contrario
*/
struct is_even {
	bool operator()(int value) const {
		return (value%2) == 0;
	}
};

/**
	@brief Funtore di controllo.
	
	Funtore da passare al printIf come predicato P
	Controlla la dimensione di un libro, se il numero di pagine 
	del libro passato come parametro superano 500, ritorna true,
	ritorna false in caso contrario
*/
struct big_book {
	bool operator()(const Book &tmp) const {
		return tmp.numero_pagine > 500;
	}
};

void test_costruttori(){

	std::cout<<"\n----------Test costruttori----------"<<std::endl;

	std::cout<<"\nTest costruttore di default"<<std::endl;
	Bst<int, compare_int, equal_int> alberoDefault;
	assert(alberoDefault.get_size() == 0);
	std::cout<<"Size dell'albero creato con il costruttore di default, la quale deve essere 0: "<<alberoDefault.get_size()<<std::endl;


	std::cout<<"\nTest costruttore secondario con array"<<std::endl;
	const int dim = 12;
	int a[dim]= {10, 5, 15, 3, 8, 20, 1, 4, 6, 9, 18, 22};
	Bst<int, compare_int, equal_int> alberoArray(a, dim);
	assert(alberoArray.get_size() == dim);
	std::cout<<"Size dell'albero creato con il costruttore secondario (con array): "<<alberoArray.get_size()<<std::endl;
	std::cout<<"Dimensione array passato come parametro: "<<dim<<std::endl;


	std::cout<<"\nTest costruttore di copia"<<std::endl;
	Bst<int, compare_int, equal_int> alberoCopia(alberoArray);
	assert(alberoCopia.get_size() == alberoArray.get_size());
	std::cout<<"Size dell'albero creato con il costruttore di copia secondario: "<<alberoCopia.get_size()<<std::endl;
	std::cout<<"Size dell'albero cpassato come parametro: "<<alberoArray.get_size()<<std::endl;


	const int dim2 = 7;
	char carray[dim2]= {'M', 'n', 'a', 'o', 'Q', 'R', 'P'};
	Bst<char, compare_char, equal_char> alberoC(carray, dim2);
	std::cout<<"\nTest operatore di assegnamento"<<std::endl;
	Bst<char, compare_char, equal_char> alberoCopia2;
	alberoCopia2 = alberoC;
	assert(alberoC.get_size() == alberoCopia2.get_size());
	std::cout<<"Size dell'albero copiato con l'operatore di assegnamento: "<<alberoCopia2.get_size()<<std::endl;
	std::cout<<"Size dell'albero risultante: "<<alberoC.get_size()<<std::endl;

}

void test_iteratori(){

	std::cout<<"\n---------- Test metodi che utilizzano gli iteratori ( printIf / exist ) ----------"<<std::endl;

	const int dim = 7;
	char carray[dim]= {'M', 'n', 'a', 'o', 'Q', 'R', 'P'};
	Bst<char, compare_char, equal_char> alberoC(carray, dim);
	int iarray[dim]= {23, 14, 25, 17, 10, 6, 76};
	Bst<int, compare_int, equal_int> alberoI(iarray, dim);
	std::string sarray[dim]= {"mil", "bicoc", "cio", "ciao", "ci", "unib", "bicocca"};
	Bst<std::string, compare_string, equal_string> alberoS(sarray, dim);
	Book barray[dim]= {Book(1234, 500), Book(1010, 400), Book(2345, 350), Book(1676, 700), Book(7234, 650), Book(6834, 800), Book(3535, 501)};
	Bst<Book, compare_books, equal_books> alberoB(barray, dim);


	std::cout<<"\nTest printIF"<<std::endl;
	std::cout<<"\nStampa dei valori in un albero che soddisfano il predicato is_even(), ossia i valori pari all'interno dell'albero: "<<std::endl;
	printIF(alberoI, is_even());

	std::cout<<"\nStampa dei valori in un albero che soddisfano il predicato big_book(), ossia i libri all'interno dell'albero che superano le 500 pagine: "<<std::endl;
	printIF(alberoB, big_book());



	std::cout<<"\nTest exist, gestito con gli assert"<<std::endl;
	assert(!alberoI.exist(15));
	alberoI.add(15);
	assert(alberoI.exist(15));

	assert(!alberoC.exist('h'));
	alberoC.add('h');
	assert(alberoC.exist('h'));

	assert(!alberoS.exist("matteo"));
	alberoS.add("matteo");
	assert(alberoS.exist("matteo"));

	assert(!alberoB.exist(Book(3456, 1000)));
	alberoB.add(Book(3456, 1000));
	assert(alberoB.exist(Book(3456, 1000)));

}

void test_intTree() {

	std::cout<<"\n---------- Test implementazione albero di interi ----------"<<std::endl;

	//add di interi 
	Bst<int, compare_int, equal_int> alberoInt;

	alberoInt.add(10);
	alberoInt.add(5);
	alberoInt.add(8);
	alberoInt.add(3);
	alberoInt.add(17);
	alberoInt.add(20);
	alberoInt.add(13);

	assert(alberoInt.get_size() == 7);

	std::cout<<"Lancio eccezione duplicateDataException:"<<std::endl;
	try{
		alberoInt.add(8);   //dovrebbe lanciare l'eccezione duplicateDataException
	}
	catch(duplicateDataException e) {
		std::cerr << e.what() << std::endl;
		assert(alberoInt.get_size() == 7); // controllo che non sia aumentata la size
	}

	std::cout<<"\nStampa di alberoInt con metodo printTree : "<<std::endl;
	alberoInt.printTree(alberoInt.get_head());

	std::cout<<"\nStampa di alberoInt con operatore<< : "<<std::endl;
	std::cout<<alberoInt<<std::endl;

	std::cout<<"\nTest subtree"<<std::endl;
	Bst<int, compare_int, equal_int> subInt;
	subInt = alberoInt.subtree(17);
	std::cout<<"Sottoalbero di alberoInt:"<<std::endl;
	std::cout<<subInt<<std::endl;

	std::cout<<"\nTest metodo clear"<<std::endl;
	alberoInt.clear();
	std::cout<<"Dimensione alberoInt dopo clear: "<<alberoInt.get_size()<<std::endl;
	assert(alberoInt.get_size() == 0);

}

void test_charTree() {

	std::cout<<"\n---------- Test implementazione albero di caratteri ----------"<<std::endl;

	//add di char 
	Bst<char, compare_char, equal_char> alberoChar;  //Costruttore di default 

	alberoChar.add('M');
	alberoChar.add('g');
	alberoChar.add('D');
	alberoChar.add('t');
	alberoChar.add('A');
	alberoChar.add('a');
	alberoChar.add('G');
	
	assert(alberoChar.get_size() == 7);

	std::cout<<"Lancio eccezione duplicateDataException:"<<std::endl;
	try{
		alberoChar.add('A');   //dovrebbe lanciare l'eccezione duplicateDataException
	}
	catch(duplicateDataException e) {
		std::cerr << e.what() << std::endl;
		assert(alberoChar.get_size() == 7); // controllo che non sia aumentata la size
	}

	std::cout<<"\nStampa di alberoChar con metodo printTree : "<<std::endl;
	alberoChar.printTree(alberoChar.get_head());
	std::cout<<"\nStampa di alberoChar con operatore<< : "<<std::endl;
	std::cout<<alberoChar<<std::endl;

	std::cout<<"\nTest subtree"<<std::endl;
	Bst<char, compare_char, equal_char> subChar;
	subChar = alberoChar.subtree('g');
	std::cout<<"Sottoalbero di alberoChar:"<<std::endl;
	std::cout<<subChar<<std::endl;

	alberoChar.clear();
	std::cout<<"\nTest metodo clear"<<std::endl;
	std::cout<<"\nDimensione alberoChar dopo clear: "<<alberoChar.get_size()<<std::endl;
	assert(alberoChar.get_size() == 0);

}

void test_stringTree() {

	std::cout<<"\n---------- Test implementazione albero di stringhe ----------"<<std::endl;

	//add di stringhe 
	Bst<std::string, compare_string, equal_string> alberoString;

	alberoString.add("ciao");
	alberoString.add("helloo");
	alberoString.add("ci");
	alberoString.add("c");
	alberoString.add("hes");
	alberoString.add("heiriiri");
	alberoString.add("ciao0");

	assert(alberoString.get_size() == 7);

	std::cout<<"Lancio eccezione duplicateDataException:"<<std::endl;
	try{
		alberoString.add("helloo");   //dovrebbe lanciare l'eccezione duplicateDataException
	}
	catch(duplicateDataException e) {
		std::cerr << e.what() << std::endl;
		assert(alberoString.get_size() == 7); // controllo che non sia aumentata la size
	}

	std::cout<<"\nStampa di alberoString con metodo printTree : "<<std::endl;
	alberoString.printTree(alberoString.get_head());
	std::cout<<"\nStampa di alberoString con operatore<< : "<<std::endl;
	std::cout<<alberoString<<std::endl;

	std::cout<<"\nTest subtree"<<std::endl;
	Bst<std::string, compare_string, equal_string> subString;
	subString = alberoString.subtree("ciao");
	std::cout<<"Sottoalbero di alberoString:"<<std::endl;
	std::cout<<subString<<std::endl;

	alberoString.clear();
	std::cout<<"Dimensione alberoString dopo clear: "<<alberoString.get_size()<<std::endl;
	assert(alberoString.get_size() == 0);

}

void test_booksTree() {

	std::cout<<"\n---------- Test implementazione albero di tipi Book ----------"<<std::endl;

	//add di oggetti Book
	Bst<Book, compare_books, equal_books> alberoBooks;

	alberoBooks.add(Book(1234, 500));
	alberoBooks.add(Book(1010, 400));
	alberoBooks.add(Book(2345, 350));
	alberoBooks.add(Book(1676, 700));
	alberoBooks.add(Book(7234, 650));
	alberoBooks.add(Book(6834, 800));
	alberoBooks.add(Book(3436, 450));

	assert(alberoBooks.get_size() == 7);

	std::cout<<"Lancio eccezione duplicateDataException:"<<std::endl;
	try{
		alberoBooks.add(Book(6834, 800));   //dovrebbe lanciare l'eccezione duplicateDataException
	}
	catch(duplicateDataException e) {
		std::cerr << e.what() << std::endl;
		assert(alberoBooks.get_size() == 7); // controllo che non sia aumentata la size
	}

	std::cout<<"\nStampa di alberoBooks con metodo printTree : "<<std::endl;
	alberoBooks.printTree(alberoBooks.get_head());
	std::cout<<"\nStampa di alberoBooks con operatore<< : "<<std::endl;
	std::cout<<alberoBooks<<std::endl;

	std::cout<<"\nTest subtree"<<std::endl;
	Bst<Book, compare_books, equal_books> subBooks;
	subBooks = alberoBooks.subtree(Book(1676, 700));
	std::cout<<"Sottoalbero di alberoBooks:"<<std::endl;
	std::cout<<subBooks<<std::endl;

	alberoBooks.clear();
	std::cout<<"Dimensione alberoBooks dopo clear: "<<alberoBooks.get_size()<<std::endl;
	assert(alberoBooks.get_size() == 0);

}




int main() { 

	test_costruttori();

	test_intTree();

	test_charTree();

	test_stringTree();

	test_booksTree();

	test_iteratori();

	return 0;
}