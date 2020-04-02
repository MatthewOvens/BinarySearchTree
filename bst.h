#ifndef BST_H
#define BST_H

#include <ostream>
#include <iterator> // std::forward_iterator_tag  //???
#include <cstddef>  // std::ptrdiff_t  			  //???


class voidTreeException : public std::logic_error {
public:
	/**
		Costruttore di default 
	*/
    voidTreeException() : std::logic_error("Operation on a void tree") {}
};

class duplicateDataException : public std::logic_error {
public:
	/**
		Costruttore di default 
	*/
    duplicateDataException() : std::logic_error("Error, duplicate data, the tree don't accept it") {}
};

/**
	Classe che implementa una lista ordinata di dati generici T. 
	L'oridnamento e' effettuati utilizzando un funtore di comparazione F.
	Di default il funtore usa l'orinamento naturale dei dati indotto dagli
	operatori di confronto standard. 

	@brief Lista ordinata

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
		Node *left;	///< puntatore al nodo figlio di sinistra 
		Node *right;	///< puntatore al nodo figlio di destra 
		Node *parent;  ///< puntatore al nodo padre 

		/**
			Costruttore di default
		*/

		Node(): left(nullptr), right(nullptr), parent(nullptr) {} 

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
			CONTROLLARE BENE IN SEGUITO SE SI FA COSI
		*/
		~Node() {
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}	

		// NOTA: per tutti gli altri metodi fondamentali vanno bene quelli di default

	}; // struct nodo

	Node *head; ///< puntatore alla radice dell'albero 
	size_type size; ///< nodi presenti all'interno dell'albero

	C conf; ///< oggetto funtore per ordinamento dei nodi all'interno dell'albero
	E eql; ///< oggetto funtore per l'uguaglianza

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
		size--;
		n = nullptr;
	}


public:

	/**
		Costruttore di default (METODO FONDAMENTALE) 
	*/
	Bst() : head(nullptr), size(0) {};

	/**
		@brief Costruttore di copia (METODO FONDAMENTALE) 

		Permette di inizializzare un nuovo albero con i valori presi da un altro albero 

		@param other albero da copiare 

		@throw voidTreeException 
		@throw .....
	*/
	explicit Bst(const Bst <T,C,E> &other): head(nullptr), size(0) {

		if(other.head != nullptr)
			helper_copy_cstr(other.head);
		else 
			throw voidTreeException();

	}


	/**
	   @brief Metodo helper per il costruttore di copia 

	   Naviga l'albero in maniera pre-order, ricorsivamente, e ad ogni chiamata 
	   aggiunge il nodo passato come parametro all'albero 

	   @param head nodo radice dal quale partire 

	   @throw ..... DA AGGIUNGERE TRY CATCH 
	   @throw .......
	*/
	void helper_copy_cstr(const Node *head) {
	
		if (head == nullptr)
			return;

		add(head->value);
		
		// Attraversamento dei rami sinistri dell'albero 
		helper_copy_cstr(head->left);

		// Attraversamento dei rami destri dell'albero 
		helper_copy_cstr(head->right);
	}

	/**
	    @brief Costruttore secondario

		Costruttore secondario che inizializza l'albero inserendo tutti i nodi presenti
		nell'array passato come parametro

		@param array  array di nodi usati per costruire l'albero
		@param dim   dimensione array  
	*/
	Bst(const value_type *array, const size_type dim): head(nullptr), size(0) {

		for(size_type i = 0; i != dim; i++){

			add(array[i]);

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

		@throw eccezione di allocazione di memoria
		@throw ........
	*/
	Bst &operator=(const Bst &other) {
		if(this != &other) {
			Bst tmp(other);  //Copy costructor
			std::swap(head,tmp.head);
			std::swap(size,tmp.size);
		}
		return *this;
	}

	/**
	    @brief Costruttore di copia secondario 

		Costruttore di copia secondario che inizializza un nuovo albero copiandolo da un altro 
		albero di tipo generico Q 

		@param other albero da copiare 

		THROW DI ECCEZIONI 

	*/
//NON E' RICHIESTO, AGGIUNGERE SE SI HA TEMPO
	/*
	template<typename Q>
	Bst(const Bst <Q> &other) : head(nullptr), size(0) {

		Bst<Q>::const_iterator ib = other.begin();
		Bst<Q>::const_iterator ie = other.end();





	}
	*/

	/**
	    @brief  Metodo di stampa dell'albero 

		Richiamando il metodo helper_print, stampa il contenuto dell'albero la cui radice 
		è stata passata come paramentro 

	    @param n Nodo radice dell'albero da stampare

		@throw voidTreeException 
	*/
	void printTree(const Node* n) const {
		
		if(n == nullptr)
			throw voidTreeException();
		else 
			helper_print(n, 0);
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
	void helper_print(const Node *n, size_type space) const {  
		 
		if (n == NULL)  
			return;  

		//aumenta la distanza in base al livello del nodo
		space += 10;  
	  
	  	//processa l'albero destro
		helper_print(n->right, space);  
	
		// stampa il nodo corrente dopo lo spazio  
		std::cout<<std::endl;  
		for (size_type i = 10; i < space; i++)  
			std::cout<<" ";  
		std::cout<<n->value<<std::endl;  
	
		// Process left child  
		helper_print(n->left, space);  
	}

	/**
	   @brief Metodo che trova il nodo col valore (value) minore nell'albero 

		Scende l'albero verso sinistra, fino a trovare l'ultimo nodo che non sia null

	   @return puntatore al nodo con il valore più piccolo 
	   @throw voidTreeException  (se gli passi un albero vuoto)
	*/
	const Node* findMin() const {

		Node* pnt = head;

		if(head != nullptr) {

			while (pnt->left != nullptr) {  

				pnt = pnt->left;
				
			}
		}
		else 
			throw voidTreeException();

		return pnt;
	}


	/**
	   @brief Metodo che trova il nodo col valore (value) maggiore nell'albero 

	   Scende l'albero verso destra, fino a trovare l'ultimo nodo che non sia null

	   @return puntatore al nodo con il valore più grande 
	   @throw voidTreeException  (se gli passi un albero vuoto)
	*/
	const Node* findMax() const {

		Node* pnt = head;

		if(head != nullptr) {

			while (pnt->right != nullptr) {  

				pnt = pnt->right;
				
			}
		}
		else 
			throw voidTreeException();

		return pnt;
	}

	/**
	    @brief Metodo che aggiunge un nodo all'albero, secondo la strategia definita dai funtori di confronto  

		@param val valore da aggiungere all'albero  
	    @throw ....................
		@throw duplicateDataException (se si aggiunge un nodo con un valore già presente nell'albero)
	*/
	void add (const value_type &val) {

		if(head == nullptr){

			//AGGIUNGERE ECCEZIONE DI ALLOCAZIONE DI MEMORIA 
			head = new Node(val);
			size++;

		}
		else {
			Node* pnt1 = head;
			Node* pnt2;

			while(pnt1 != nullptr){

				if(eql(val, pnt1->value)){

					throw duplicateDataException();
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

			//AGGIUNGERE ECCEZIONE ALLOCAZONE MEMORIA FARE TRY CATCH
			Node* newNode = new Node(val);

			newNode->parent = pnt2;	

			size++;	

			if(conf(val, pnt2->value))
				pnt2->left = newNode;
			else 
				pnt2->right = newNode;
		}
	}

	/**
	    @brief Metodo che permette di conoscere il numero totale di dati inseriti nell'albero

	    @return la size dell'albero, ossia il numero di nodi al suo interno  
	*/
	size_type get_size() const {
		return size;
	}

	/**
	    @brief Metodo che permette di accedere al nodo radice dell'albero 

	    @return il puntatore al nodo radice dell'albero   
	*/
	const Node* get_head(){

		return head;

	}

 	/**
	    @brief Cancella il contenuto dell'albero  
	*/

	void clear() {
		helper_clear(head);
		head = nullptr;
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

	//ASSICURARSI SIANO GIUSTIIII
		typedef std::forward_iterator_tag  	iterator_category;
		typedef Node                    	value_type;
		typedef ptrdiff_t                 	difference_type;
		typedef const Node*              	pointer;
		typedef const Node&               	reference;

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
  
			
			if (n->right != nullptr)
			{
				n = n->right;
				
				while (n->left != nullptr) {
				n = n->left;
				}
			}
			else
			{
				// have already processed the left subtree, and
				// there is no right subtree. move up the tree,
				// looking for a parent for which nodePtr is a left child,
				// stopping if the parent becomes NULL. a non-NULL parent
				// is the successor. if parent is NULL, the original node
				// was the last node inorder, and its successor
				// is the end of the list
				p = n->parent;
				while (p != nullptr && n == p->right)
				{
					n = p;
					p = p->parent;
				}
				
				// if we were previously at the right-most node in
				// the tree, nodePtr = nullptr, and the iterator specifies
				// the end of the list
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
  
			
			if (n->right != nullptr)
			{
				n = n->right;
				
				while (n->left != nullptr) {
				n = n->left;
				}
			}
			else
			{
				// have already processed the left subtree, and
				// there is no right subtree. move up the tree,
				// looking for a parent for which nodePtr is a left child,
				// stopping if the parent becomes NULL. a non-NULL parent
				// is the successor. if parent is NULL, the original node
				// was the last node inorder, and its successor
				// is the end of the list
				p = n->parent;
				while (p != nullptr && n == p->right)
				{
					n = p;
					p = p->parent;
				}
				
				// if we were previously at the right-most node in
				// the tree, nodePtr = nullptr, and the iterator specifies
				// the end of the list
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















};




#endif