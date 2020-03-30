#ifndef BST_H
#define BST_H

#include <ostream>
#include <iterator> // std::forward_iterator_tag  //???
#include <cstddef>  // std::ptrdiff_t  			  //???


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
template <typename T>      // typename C, typename E>
class Bst {

public: 

	typename insigned int size_type;

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
			Costruttore secondario che inizializza il nodo
			@param v valore del dato
			@param n_dx puntatore al nodo figlio di destra
			@param n_sx puntatore al nodo figlio di sinistra
			@param n_parent puntatore al nodo figlio di sinistra
		*/
		Node(const T &v, Node *n_sx, Node *n_dx, Node *n_parent) {
			
			value = v;
					
			assert(n_dx->value > value && "Errore, parametri errati per un albero binario di ricerca");
			assert(n_sx->value < value && "Errore, parametri errati per un albero binario di ricerca");
					
			parent = n_parent;
			left = n_sx;
			right = n_dx;	
		}
				
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

private:

	Node *head; ///< puntatore alla radice dell'albero 
	static size_type size; ///< nodi presenti all'interno dell'albero

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
	explicit Bst(const Bst &other): head(nullptr), size(0) {

		head = other.head;


	}



	/**
		@brief Costruttore secondario 

		Costruttore secondario che inizializza l'albero con la sua radice

		@param n  nodo da inserire come radice
	*/
	explicit Bst(const Node &n): head(nullptr), size(0) {
		

		add(n);

		/*Node *pnt = &n;
		head = pnt;
		size++;
		*/
	}

	/**
	    @brief Costruttore secondario

		Costruttore secondario che inizializza l'albero inserendo tutti i nodi presenti
		nell'array passato come parametro

		@param array  array di nodi usati per costruire l'albero
		@param dim   dimensione array  
	*/
	Bst(const *array, unsigned int dim): head(nullptr), size(0) {

		for(int i = 0, i != dim, i++){

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
	template<typename Q>
	Bst(const Bst <Q> &other) : head(nullptr), size(0) {

		Bst<Q>::const_iterator ib = other.begin();
		Bst<Q>::const_iterator ie = other.end();





	}

	void print() {

		cout<< size <<endl;

	}





//DA MODIFICAR TUTTO L'ITERATORE 


	/**
		Iteratore costante dell'albero

		@brief Iteratore costante dell'albero
	*/
	class const_iterator {
		const node *n;  ///< puntatore alla posizone (nodo) dell'iteratore nell'albero 

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class Bst;

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		iterator(const Node *nodo) : n(nodo){}

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

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
			_n = other._n;
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
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			_n = _n->next;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			_n = _n->next;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return (_n == other._n);
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return (_n != other._n);
		}
	}; // classe const_iterator
	
	/**
		@brief Metodo che ritorna l'iteratore all'inizio della sequenza dati
	
		@return iteratore all'inizio della sequenza
	*/
	const_iterator begin() const {
		return const_iterator(_head);
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