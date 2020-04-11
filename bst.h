#ifndef BST_H
#define BST_H

#include <ostream>
#include <iterator> // std::forward_iterator_tag  
#include <cstddef>  // std::ptrdiff_t  			  


/**
   @brief Eccezione custom

   Viene lanciata quando si tenta di inserire un dato T gia' esistente all'interno dell'albero
*/
class duplicateDataException {
private:

	std::string message;

public: 
	/**
		Costruttore 
	*/
	duplicateDataException(const std::string message) {
		this->message = message;
	}

	std::string get_message() {
		return message;
	}
};


/**
	Classe che implementa un albero binario di ricerca di dati generici T. 
	Il confronto tra dati T e' effettuato utilizzando due funtori di comparazione
	uno per l'uguaglianza (E), l'altro per il confronto (C)
	La strategia di confronto tra dati grazie a questi due funtori e' definibile 
	dall'utente alla creazione dell'albero.

	@brief Generic Binary Serach Tree 

	@param T tipo del dato
	@param C funtore di comparazione (<) di due dati
	@param E funtore di comparazione (==) di due dati
*/
template <typename T, typename C, typename E>
class Bst {

public: 
	typedef unsigned int size_type;
	typedef T value_type;

private:

	/**
		Struttura di supporto interna che implementa un nodo dell'albero.

		@brief Nodo dell'albero
	*/
	struct Node {
		value_type value;  ///< Dato inserito nel nodo 
		Node *left;		///< puntatore al nodo figlio di sinistra 
		Node *right;	///< puntatore al nodo figlio di destra 
		Node *parent;  ///< puntatore al nodo padre 

		/**
			Costruttore di default
		*/
		Node(): left(nullptr), right(nullptr), parent(nullptr), value(nullptr){} 

		/**
			Costruttore secondario che inizializza il nodo

			@param v valore del dato
		*/
		Node(const value_type &v) : value(v), left(nullptr), right(nullptr), parent(nullptr){}

		/**
			Costruttore secondario che inizializza il nodo con i rispettivi nodo figlio sinistro,
			nodo figlio destro e parent  

			@param v valore del dato
			@param n_left puntatore al nodo figlio di sinistra
			@param n_right puntatore al nodo figlio di destra
			@param n_parent puntatore al nodo parent
		*/
		Node(const value_type &v, Node *n_left, Node *n_right, Node *n_parent)
		 : value(v), parent(n_parent), left(n_left), right(n_right) {}

		/**
			Costruttore secondario che inizializza il nodo con i rispettivi nodo figlio sinistro e nodo figlio destro  

			@param v valore del dato
			@param n_left puntatore al nodo figlio di sinistra
			@param n_right puntatore al nodo figlio di destra
		*/
		Node(const value_type &v, Node *n_left, Node *n_right)
		 : value(v), parent(nullptr), left(n_left), right(n_right) {}
			
		/**
			Distruttore 
		*/
		~Node() {
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}	

		// NOTA: per tutti gli altri metodi fondamentali vanno bene quelli di default

	}; //fine struct Node

	Node *_head; ///< puntatore alla radice dell'albero 
	size_type _size; ///< nodi presenti all'interno dell'albero

	C conf; ///< oggetto funtore per il confronto
	E eql;  ///< oggetto funtore per l'uguaglianza

	/**
	    @brief Metodo helper per il clear()

	    Naviga l'albero in maniera post-order, ricorsivamente, cancellando tutti
	    i nodi appartenenti all'albero la cui radice è stata passata come parametro 

		@param n nodo radice dell'albero da cancellare
	*/
	void helper_clear(Node *n) {

		if (n == nullptr)
			return;

		// attraversa il sottoalbero di sinistra 
		helper_clear(n->left);

		// attraversa il sottoalbero di destra 
		helper_clear(n->right);

		//eliminazione del nodo 
		delete n;
		_size--;
		n = nullptr;
	}


	/**
	    @brief Metodo helper per il metodo print

		Ricorsivamente, processando prima i rami destri dell'albero, poi quelli sinistri 
		stampa orizzontalmente il contenuto dell'albero, seguendo un struttura
		simil-albero binario

		@param n nodo di partenza, si passa la radice dell'albero che si vuole stampare 
		@param space numero intero che viene incrementato di 10 dipendentemente dalla 
					 profondità del nodo che bisogna stampare
	*/  
	void helper_print(const Node *n, unsigned int space) const {  
		 
		if (n == nullptr)  
			return;  

		//aumenta la distanza in base al livello del nodo
		space += 10;  
	  
	  	//processa il ramo destro
		helper_print(n->right, space);  
	
		// stampa il nodo corrente dopo lo spazio  
		std::cout<<std::endl;  
		for (unsigned int i = 10; i < space; i++)  
			std::cout<<" ";  
		std::cout<<n->value<<std::endl;  
	
		// processa il ramo sinistro  
		helper_print(n->left, space);  
	}

	/**
		@brief Metodo helper per il costruttore di copia 

		Naviga l'albero in maniera pre-order, ricorsivamente, e ad ogni chiamata 
		aggiunge il nodo passato come parametro all'albero 

		@param head nodo radice dal quale partire 

		@throw eccezione di allocazione di memoria (runtime)
	*/
	void helper_copy_cstr(const Node *head) {
	
		if (head == nullptr)
			return;

		try {
			add(head->value);
		}
		catch(...){
			clear();
			throw;
		}
		
		// Attraversamento dei rami sinistri dell'albero 
		helper_copy_cstr(head->left);

		// Attraversamento dei rami destri dell'albero 
		helper_copy_cstr(head->right);
	}

	/**
	    @brief Metodo che trova il nodo col valore (value) minore nell'albero 

		Scende l'albero verso sinistra, fino a trovare l'ultimo nodo che non sia null
		Se viene chiamata su un albero vuoto, ritorna il puntatore a null

	    @return puntatore al nodo con il valore più piccolo   
	*/
	const Node* findMin() const {

		Node* pnt = _head;

		if(_head != nullptr) {

			while (pnt->left != nullptr) {  

				pnt = pnt->left;
				
			}
			return pnt;
		}
		else 
			return pnt;
	}


public:

	/**
		Costruttore di default (METODO FONDAMENTALE) 
	*/
	Bst() : _head(nullptr), _size(0) {};

	/**
		@brief Costruttore di copia (METODO FONDAMENTALE) 

		Permette di inizializzare un nuovo albero con i valori presi da un altro albero 

		@param other albero da copiare 

		@throw eccezione di allocazione di memoria (runtime)
	*/
	Bst(const Bst <T,C,E> &other): _head(nullptr), _size(0) {
		
		if(other._head != nullptr)
			helper_copy_cstr(other._head);
		else {
			_head = nullptr;      //se gli si passa un albero vuoto, quello corrente lo inizializzo con i dati membro 
			_size = 0;			 //di default, evitando di lanciare un'eccezione
		}
		
	}

	/**
	    @brief Costruttore secondario

		Costruttore secondario che inizializza l'albero inserendo tutti i nodi presenti
		nell'array passato come parametro

		@param array  array di nodi usati per costruire l'albero
		@param dim   dimensione array 

		@throw eccezione di allocazione di memoria (runtime)
		@throw duplicateDataException
	*/
	Bst(const value_type *array, const unsigned int dim): _head(nullptr), _size(0) {

		for(unsigned int i = 0; i != dim; i++){
			try {
				add(array[i]);
			}
			catch(...){
				clear();
				throw;
			}
		}
	}

	/**
	    @brief Distruttore  
	*/
	~Bst() {
		clear();
	}

	/**
		@brief Operatore di assegnamento
		
		@param other albero da copiare

		@return reference a this

		@throw eccezione di allocazione di memoria (runtime)
	*/
	Bst &operator=(const Bst &other) {
		if(this != &other) {
			Bst tmp(other);  //Copy costructor
			std::swap(_head,tmp._head);
			std::swap(_size,tmp._size);
		}
		return *this;
	}

	/**
	    @brief  Metodo di stampa dell'albero 

		Richiamando il metodo helper_print, stampa il contenuto dell'albero la cui radice 
		è stata passata come paramentro 

	    @param n Nodo radice dell'albero da stampare
	*/
	void printTree(const Node* n) const {
		
		if(n == nullptr)
			std::cerr<<"Albero vuoto, niente da stampare"<<std::endl;  //Se gli si passa un nodo radice null, e quindi un albero vuoto, 						   
		else 					   									   //stampa un messaggio di errore, evitando di lanciare un'eccezione
			helper_print(n, 0);
	}

	/**
	    @brief Metodo che aggiunge un nodo all'albero, secondo la strategia definita dai funtori di confronto  

		@param val valore da aggiungere all'albero  

	    @throw eccezione di allocazione di memoria (runtime)
		@throw duplicateDataException
	*/
	void add (const value_type &val) {

		if(_head == nullptr){

			try {
				_head = new Node(val);
				_size++;
			}
			catch(...){  //Non c'e' bisogno di aggiungere _head = nullpnt perche' e' condizione dell'if in cui siamo
				throw;
			}
		}
		else {
			Node* pnt1 = _head;
			Node* pnt2;

			while(pnt1 != nullptr){

				if(eql(val, pnt1->value)){

					throw duplicateDataException("Error, duplicate data, the tree don't accept it");

				}
				else if(conf(val, pnt1->value)) {   //se val è minore di pnt1->value 
					pnt2 = pnt1;
					pnt1 = pnt1->left;
				}
				else if(!conf(val, pnt1->value)){  //se val è maggiore di pnt1->value
					pnt2 = pnt1;
					pnt1 = pnt1->right;
				}

			}

			try {
				Node* newNode = new Node(val);

				newNode->parent = pnt2;	

				_size++;	

				if(conf(val, pnt2->value))
					pnt2->left = newNode;
				else 
					pnt2->right = newNode;
			}
			catch(...){
				clear();
				throw;
			}
		}
	}

	/**
	    @brief Metodo che permette di conoscere il numero totale di dati inseriti nell'albero

	    @return la size dell'albero, ossia il numero di nodi al suo interno  
	*/
	const size_type get_size() const {
		return _size;
	}

	/**
	    @brief Metodo che permette di accedere al nodo radice dell'albero 

	    @return il puntatore al nodo radice dell'albero 
	*/
	const Node* get_head() const {
		return _head;
	}

 	/**
	    @brief Cancella il contenuto dell'albero  
	*/
	void clear() {
		helper_clear(_head);
		_head = nullptr;
	}

	/**
	    @brief Metodo di controllo esistenza di un elemento T all'interno dell'albero 

		Con l'aiuto degli iteratori il metodo naviga l'intero albero in cerca del valore 
		passato come argomento
		L'uguaglianza è definita dal funtore di confronto eql

		@param value elemento da cercare tra i nodi dell'albero 

		@return true se il valore viene trovato, false altrimenti
	*/
	bool exist(const value_type &value) const{

		if(_head != nullptr){
			const_iterator i = begin();
			const_iterator ie = end();

			while(i != ie){

				if(eql(value, *i))
					return true;
				
				++i;
			}

			return false;
		}
		else 
			return false;
	}

	/**
	    @brief Metodo subtree

		Ritorna un nuovo albero, il quale deve corrispondere al sottoalbero 
		avente come radice il nodo con il valore passato come parametro 

		@param value valore di un nodo da cercare all'interno dell'albero sul quale è stato
					 chiamato il metodo, e che sarà la radice del sottoalbero risultante

		@return il sottoalbero risultante, se si fa il subtree su un albero vuoto o su un albero in cui 
				non e' presente il valore passato come paramentro, il metodo ritorna un albero vuoto

		@throw eccezione di allocazione di memoria (runtime)
	*/
	Bst subtree(const value_type &value) const{

		const_iterator i = begin();
		const_iterator ie = end();

		Bst newTree;
		
		while(i != ie){
			
			if(eql(*i, value)){
				newTree.helper_copy_cstr(i.n);
				return newTree;
			}
			else 
				++i;
		}

		return newTree;	
	}

	

	/**
		Iteratore costante (CONST) dell'albero

		@brief Iteratore costante dell'albero
	*/
	class const_iterator {
		const Node *n;  ///< puntatore alla posizone (nodo) dell'iteratore nell'albero 

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Bst;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const Node *nodo) : n(nodo){}

	public:

		typedef std::forward_iterator_tag  	iterator_category;
		typedef T                    		value_type;
		typedef ptrdiff_t                 	difference_type;
		typedef const T*              		pointer;
		typedef const T&               		reference;

		/**
		   @brief Costruttore di default 
		*/
		const_iterator() : n(nullptr) {
		}
		
		/**
		   @brief Costruttore di copia 

		   @param other un altro iteratore costante da copiare 
		*/
		const_iterator(const const_iterator &other) : n(other.n) {
		}

		/**
		   @brief Operatore di assegnamento

		   @param other un altro iteratore costante
		   @return riferimento all'iteratore 
		*/
		const_iterator& operator=(const const_iterator &other) {
			n = other.n;
			return *this;
		}

		/**
		   @brief Distruttore
		*/
		~const_iterator() {}

		/**
		   @brief Operatore di dereferenziazione

		   @return il dato riferito dall'iteratore (dereferenziamento)
		*/
		reference operator*() const {
			return n->value;
		}

		/**
		   @brief Operatore ->

		   @return il puntatore al dato riferito dall'iteratore 
		*/
		pointer operator->() const {
			return &(n->value);
		}
		
		/**
		 	@brief Operatore di iterazione post-incremento (X++)
		
			@return l'iteratore prim dell'incremento
		*/
		const_iterator operator++(int) {

			const_iterator tmp(*this);
			
			Node *p;  //puntatore di appoggio
  
			
			if (n->right != nullptr) {
				n = n->right;
				
				while (n->left != nullptr) {
				n = n->left;
				}
			}
			else
			{
				p = n->parent;
				while (p != nullptr && n == p->right){
					n = p;
					p = p->parent;
				}
				
				n = p;
			}
			return tmp;
		}

		/**
		 	@brief Operatore di iterazione pre-incremento (++X)

			@return l'iteratore incrementato
		*/ 
		const_iterator& operator++() {

			Node *p;  //puntatore di appoggio
  
			
			if (n->right != nullptr) {
				n = n->right;
				
				while (n->left != nullptr) {
				n = n->left;
				}
			}
			else
			{
				p = n->parent;
				while (p != nullptr && n == p->right) {
					n = p;
					p = p->parent;
				}
				
				n = p;
			}
		
			return *this;
		}

		/**
		    @brief Operatore di uguaglianza 

		   Ridefinizione dell'operatore di uguaglianza 

			@param other iteratore da confrontare
		    @return un booleano, il risultato dell'uguaglianza TRUE se sono uguali, FALSE se sono diversi 
		*/
		bool operator==(const const_iterator &other) const {
			return (n == other.n);
		}
		
		/**
		    @brief Operatore di disuguaglianza 

		   	Ridefinizione dell'operatore di disuguaglianza 

			@param other iteratore da confrontare
		    @return un booleano, il risultato dell'uguaglianza TRUE se sono diversi, FALSE se sono uguali 
		*/
		bool operator!=(const const_iterator &other) const {
			return (n != other.n);
		}
	}; // classe const_iterator
	
	/**
		@brief Metodo che ritorna l'iteratore all'inizio della sequenza dati
	
		@return iteratore all'inizio della sequenza
	*/
	const_iterator begin() const {
		return const_iterator(findMin()); 
	}
	
	/**
		@brief Metodo che ritorna l'iteratore alla fine della sequenza dati
	
		@return iteratore alla fine della sequenza
	*/
	const_iterator end() const {
		return const_iterator(nullptr);
	}
}; //Fine classe Bst



/**
	@brief Ridefinizione dell'operatore di stream per la stampa del contenuto
		   dell'albero

	@param os oggetto stream di output
	@param ot albero da stampare

	@return reference allo stream di output
*/
template <typename T, typename C, typename E>
std::ostream &operator<<(std::ostream &os, const Bst<T,C,E> &ot) {
	
	ot.printTree(ot.get_head());

	return os;
}

/**
	@brief  Funzione globale printIF che dato un albero binario di tipo T, e un predicato P, 
			stampa a schermo tutti i valori contenuti nell’albero che soddisfano il predicato
	
	@param ot albero del quale vanno conrollati tutti i nodi affinchè siano acettati dal predicat
	@param pred predicato 
*/
template <typename T, typename C, typename E, typename P>
void printIF(const Bst<T,C,E> &ot, P pred) {
	
	typename Bst<T,C,E>::const_iterator i, ie;
	
	i = ot.begin();
	ie = ot.end();
	
	while(i!=ie) {
		if(pred(*i)) {
			std::cout << *i << " ";
		}
		++i;
	}
	std::cout<<std::endl;
}

#endif