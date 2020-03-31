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

private:

	/**
		Struttura di supporto interna che implementa un nodo dell'albero.

		@brief Nodo dell'albero
	*/
	struct Node {
		T value;  ///< Dato inserito nel nodo 
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
		Node(const T &v) : value(v), left(nullptr), right(nullptr), parent(nullptr){}

		/**
			Costruttore secondario che inizializza il nodo "legandolo" al suo parente
			@param v valore del dato
			@param n_parent puntatore al nodo figlio di sinistra
		*/
		// Node(const T &v, Node *n_parent) : value(v), parent(n_parent), left(nullptr), right(nullptr) {}
			
		/**
			Distruttore 
			CONTROLLARE BENE IN SEGUITO SE SI FA COSI
		*/
		~Node() {
			delete this;
			delete left;
			delete right;
			delete parent;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}	

		// NOTA: per tutti gli altri metodi fondamentali vanno bene quelli di default

	}; // struct nodo

	Node *head; ///< puntatore alla radice dell'albero 
	unsigned int size; ///< nodi presenti all'interno dell'albero

	C conf; ///< oggetto funtore per ordinamento dei nodi all'interno dell'albero
	E eql; ///< oggetto funtore per l'uguaglianza

public:

	/**
		Costruttore di default (METODO FONDAMENTALE) 
	*/
	Bst() : head(nullptr), size(0) {};

	/**
		@brief Costruttore di copia (METODO FONDAMENTALE) 

		Permette di inizializzare un nuovo albero con i valori presi da un altro albero 

		@param other albero da copiare 

		provo a farlo dopo con l'iteratore

		THROW DI ECCEZIONI 
	*/
	explicit Bst(const Bst <T,C,E> &other): head(nullptr), size(0) {

		head = other.head;
		size = other.getSize();

		const 

	}



	/**
		@brief Costruttore secondario 

		Costruttore secondario che inizializza l'albero con la sua radice

		@param n  nodo da inserire come radice
	*/
/*
	explicit Bst(const Node &n): head(nullptr), size(0) {
		

		add(n);

		
	}
	*/
	

	/**
	    @brief Costruttore secondario

		Costruttore secondario che inizializza l'albero inserendo tutti i nodi presenti
		nell'array passato come parametro

		@param array  array di nodi usati per costruire l'albero
		@param dim   dimensione array  
	*/
	Bst(const T *array, unsigned int dim): head(nullptr), size(0) {

		for(int i = 0; i != dim; i++){

			add(array[i]);

		}
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

	void print() {

		std::cout<<"dimensione: "<< size <<std::endl;

	}

	/**
	   @brief Metodo che trova il nodo col valore (value) minore nell'albero 

		Scende l'albero verso sinistra, fino a trovare l'ultimo nodo che non sia null

	   @return puntatore al nodo con il valore più piccolo 
	   @throw voidTreeException  (se gli passi un albero vuoto)
	*/
	Node* findMin() const {

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
	Node* findMax() const {

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
	    @brief Metodo che aggiunge un nodo all'albero, secondo la strategia definita dal funtore di confronto  

		@param n nodo da aggiungere all'albero 
		@param 
	    @throw ....................
	*/
	void add (const T &val) {

		if(head == nullptr){

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
	   @brief Metodo che trova il nodo col valore (value) maggiore nell'albero 

	   Scende l'albero verso destra, fino a trovare l'ultimo nodo che non sia null

	   @return puntatore al nodo con il valore più grande 
	*/
	unsigned int getSize() const {
		return size;
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