#ifndef logicarray_h
#define logicarray_h
#include <ostream>
#include <iterator>
#include <cstddef>
#include <stdexcept>
#include "log.h"
/**
@file sortedarray.h
@brief Dichiarazione classe sortedarray

**/

/**
@brief Array di tipo T

La classe contiene due array uno con i dati non ordinati e uno con le posizioni in maniera tale
che i dati se letti leggendo sequenzialmente le posizioni dal secondo array risultino ordinati
**/
template <typename T, typename F>
class sortedarray
{
	typedef unsigned int maxDimension;
	
	F comp_; /**< Funtore di ordinamento */

	unsigned int last_inserted_; /**< Contatore di elementi inseriti */

	int* head_;/**< puntatore alla testa ordinata */
	int* tail_;/**< puntatore alla coda ordinata */

	T* uhead_;/**< puntatore alla testa non ordinata */
	T* utail_;/**< puntatore alla coda non ordinata */
	maxDimension dimensione_array_;/**< Dimensione massima dell'array */

	Logger logger_;/**< Classe logger x cout a video */
protected:
	T * unsorted_data_;/**< Array di dati non ordinati */
	int* sorted_data_;/**< Array per gestire la posizione dei dati in maniera ordinata */
public:
	//COSTRUTTORI E DISTRUTTORE
	/**
	*	Inizializza un nuovo sortedarray di tipo T con dimensione 0
	* 	@brief Costruttore Priamario
	*
	**/
	sortedarray() : last_inserted_(0), head_(0), tail_(0), uhead_(0), utail_(0), dimensione_array_(0), logger_(Logger::WARNING), unsorted_data_(0), sorted_data_(0)
	{
	}
	/**
	*	Inizializza un nuovo sortedarray di tipo T con dimensione size
	* 	@brief Costruttore Secondario
	*	@param dimensione Dimensione dell'array da creare
	*
	**/
	sortedarray(const maxDimension dimensione) : last_inserted_(0), head_(0), tail_(0), uhead_(0), utail_(0), dimensione_array_(0), logger_(Logger::WARNING), unsorted_data_(0), sorted_data_(0)
	{
		try {
			dimensione_array_ = dimensione;
			unsorted_data_ = new T[dimensione];
			sorted_data_ = new int[dimensione];

			head_ = &sorted_data_[0];
			tail_ = &sorted_data_[0];

			uhead_ = &unsorted_data_[0];
			utail_ = &unsorted_data_[0];

			last_inserted_ = 0;
		}
		catch (std::exception& e) {
			std::cerr << "exception caught: " << e.what() << '\n';
		}
	}
	/**
	*	Copy constructor
	* 	@brief Copy constructor
	*	@param other sortedarray da copiare
	*
	**/
	sortedarray(const sortedarray &other) :last_inserted_(0), head_(0), tail_(0), uhead_(0), utail_(0), dimensione_array_(0), logger_(Logger::WARNING), unsorted_data_(0), sorted_data_(0)
	{
		try {
			unsorted_data_ = new T[other.dimensione_array_];
			sorted_data_ = new int[other.dimensione_array_];

			last_inserted_ = other.last_inserted_;

			head_ = other.head_;
			tail_ = other.tail_;

			uhead_ = other.uhead_;
			utail_ = other.utail_;

			dimensione_array_ = other.dimensione_array_;
			comp_ = other.comp_;

			for (int i = 0; i < dimensione_array_; i++)
			{
				unsorted_data_[i] = other.unsorted_data_[i];
				sorted_data_[i] = other.sorted_data_[i];
			}
		}
		catch (...)
		{
			logger_.log(Logger::ERROR, "Impossibile usare il copyconstructor");
			dispose();
		}
	}
	/**
	*	costruttore che prende in input la grandezza del sortedarray che si vuole creare,
	*	se la creazione non va a buon fine viene catturata l'eccezione specifica
	* 	@brief costruttore con dimensione
	*	@param inizio pointer a inizio array da copiare
	*	@param fine pointer a fine array da copiare
	*	@param dimensione numero di elementi 
	*	@param comp funtore di ordinamento
	**/
	template <typename IterT>
	sortedarray(IterT inizio, IterT fine, const maxDimension dimensione, F comp) : last_inserted_(0), head_(0), tail_(0)
	{
		dimensione_array_ = dimensione;
		unsorted_data_ = new T[dimensione];
		sorted_data_ = new int[dimensione];
		uhead_ = &unsorted_data_[0];
		head_ = &sorted_data_[last_inserted_];
		try
		{
			for (; inizio != fine; ++inizio)
				insertData(static_cast<T>(*inizio));
		}
		catch (std::invalid_argument &e)
		{
			cout << e.what() << std::endl;
		}
		catch (std::out_of_range &e)
		{
			cout << e.what() << std::endl;
		}
		catch (...)
		{
			logger_.log(Logger::ERROR, "Eccezione sconosciuta");
		}
	}
	/**@brief distruttore di default */
	~sortedarray()
	{
		if (!dispose())
			logger_.log(Logger::ERROR, "Impossibile eseguire il dispose delle risorse. Possibili memory leak");
	}
	//END COSTRUTTORI E DISTRUTTORE

	//-----------------------------

	//GET E SET PARAMETRI
	/**@brief ritorna l'elemento in testa all'array non ordinato */
	T getUnsortedHead()
	{
		return uhead_;
	}
	/**@brief ritorna l'elemento in coda all'array non ordinato */
	T getUnsortedTail()
	{
		return utail_;
	}
	/**@brief  Ritorna la dimensione dell'array */
	maxDimension getDimension() const
	{
		return this->dimensione_array_;
	}
	/**@brief  Restituisce il numero di posizioni ancora libere */
	int getFreeSpace() const
	{
		return this->dimensione_array_ - this->last_inserted_ > 0 ? this->dimensione_array_ - this->last_inserted_ : 0;
	}
	/**@brief  Ritorna l'elemento in testa*/
	T getHead()
	{
		return this->head_;
	}
	/**@brief Ritorna l'elemento in coda*/
	T getTail()
	{
		return this->tail_;
	}
	/**@brief contatore se indica quanti elementi sono stati inseriti */
    int getLastInserted() const
	{
		return last_inserted_;
	}
	//END GET E SET PARAMETRI

	//-----------------------------

	//METODI E FUNZIONI
	/**@brief  Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
	 * @param data Valore T da inserire nell'array
	 */
	bool insertData(const T& data)
	{
		if (last_inserted_ == dimensione_array_)
			throw std::out_of_range("Array pieno, impossibile inserire ulteriori elementi");
		try {
			unsorted_data_[last_inserted_] = data;
			bool inserito = false;
			unsigned int i;
			for (i = 0; i < last_inserted_; i++)
			{
				if (!comp_(data, unsorted_data_[sorted_data_[i]]) && !inserito)
				{
					shiftItem(i);
					sorted_data_[i] = last_inserted_;
					inserito = true;
				}
			}
			if (!inserito)
				sorted_data_[i] = last_inserted_;
			tail_ = &sorted_data_[last_inserted_];
			utail_ = &unsorted_data_[last_inserted_];
			last_inserted_++;
		}
		catch (std::exception& e) {
			std::cerr << "exception caught: " << e.what() << '\n';
			return false;
		}
		return true;
	}
	/**@brief  Svuota l'array da tutti i dati. Svuota anche l'array delle posizioni*/
	bool emptyData()
	{
		logger_.log(Logger::INFO, "Inizio procedura di svuotamento");
		try {
			last_inserted_ = 0;
			T* current = head_;
			int pos = 0;
			while (current != tail_) {
				*current = 0;
				sorted_data_[pos] = 0;
				++current;
				pos++;
			}
			tail_ = head_;
		}
		catch (std::exception& e) {
			std::cerr << "exception caught: " << e.what() << '\n';
			return false;
		}
		logger_.log(Logger::INFO, "Fine procedura di svuotamento");
		return true;
	}
	/**@brief  Metodo ausiliario utilizzato nell'operatore assegnamento
	 * @param to_swap sortedarray da copiare
	 */
	void swap(sortedarray& to_swap)
	{
		try {
			std::swap(to_swap.last_inserted_, this->last_inserted_);
			std::swap(to_swap.unsorted_data_, this->unsorted_data_);
			std::swap(to_swap.dimensione_array_, this->dimensione_array_);
			std::swap(to_swap.head_, this->head_);
			std::swap(to_swap.tail_, this->tail_);
			std::swap(to_swap.sorted_data_, this->sorted_data_);
		}
		catch (std::exception& e) {
			std::cerr << "exception caught: " << e.what() << '\n';
		}
	}
	/**@brief cancellazione e svuotamento*/
	bool dispose()
	{
		try {
			logger_.log(Logger::WARNING, "Inizio dispose delle risorse");
			delete[] unsorted_data_;
			delete[] sorted_data_;
			last_inserted_ = 0;
			head_ = 0;

			tail_ = 0;

			dimensione_array_ = 0;
			logger_.log(Logger::WARNING, "Fine dispose delle risorse");
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	/**@brief Shifta a dx di 1 posizione ogni elemento 
	 * @param position posizione da cui shiftare
	 */
	void shiftItem(int position) const
	{
		int temp = sorted_data_[getDimension() - 1];
		for (unsigned int i = position; i < getDimension(); i++) {
			const int temp1 = sorted_data_[i];
			sorted_data_[i] = temp;
			temp = temp1;
		}
		cout << std::endl;
	}
	/**@brief stampa ordinata degli elementi nell'array */
	void sortedPrint()
	{
		std::cout << "SORTED PRINT\n";
		for (unsigned int i = 0; i < last_inserted_; i++)
			std::cout << "Posizione:\t" << sorted_data_[i] << "\tValore:\t" << unsorted_data_[sorted_data_[i]] << "\n";
		std::cout << "---------- END SORTED PRINT-----------------\n";
	}
	/**@brief stampa in ordine di inserimento nell'array */
	void unsortedPrint()
	{
		std::cout << "----------- UNSORTED PRINT ------------\n";
		for (unsigned int i = 0; i < last_inserted_; i++)
			std::cout << "Posizione:\t" << i << "\tValore:\t" << unsorted_data_[i] << "\n";
		std::cout << "---------- END UNSORTED PRINT-----------------\n";
	}
	//END METODI E FUNZIONI

	//-----------------------------

	//OPERATOR OVERLOADING
	/**@brief operatore di assegnamento per LogicArray 
	 * @param other sortedarray da assegnare
	 */
	sortedarray& operator=(const sortedarray& other)
	{
		if (this != other)
		{
			sortedarray tmp(other);
			this->swap(tmp);
		}
		return *this;
	}
	/**@brief Operatore di accesso indexato ai dati ordinati const 
	 * @param index posizione a cui accedere
	 */
	const T &operator[](const maxDimension index) const
	{
		return unsorted_data_[sorted_data_[index]];
	}
	/**@brief Operatore di accesso indexato ai dati ordinati 
	 * @param index posizione a cui accedere
	 */
	T &operator[](const maxDimension index)
	{
		return unsorted_data_[sorted_data_[index]];
	}
	/**@brief Operatore di accesso indexato ai dati non ordinati const 
	 * @param index posizione a cui accedere
	 */
	const T &operator()(const maxDimension index) const
	{
		return unsorted_data_[index];
	}
	/**@brief Operatore di accesso indexato ai dati non ordinati 
	 * @param index posizione a cui accedere
	 */
	T &operator()(const maxDimension index)
	{
		return unsorted_data_[index];
	}
	//END OPERATOR OVERLOADING

	//ITERATORI
	class const_iterator;
	class u_const_iterator {
		const T *data;
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef const T*                 pointer;
		typedef const T&                 reference;

		/**@brief Costruttore di default */
		u_const_iterator() : data(0) {}

		/**@brief copyconstructor 
		 * @param other iteratore da copiare
		 */
		u_const_iterator(const u_const_iterator &other) : data(other.data) {

		}
		/**@brief operatore di assegnamento
		* @param other iteratore da copiare
		*/
		u_const_iterator& operator=(const u_const_iterator &other) {
			data = other.data;
			return *this;
		}
		/**@brief distruttore di default
		*/
		~u_const_iterator() {
			data = 0;
		}

		//altri metodi

		/**@brief (dereferenziamento) */
		reference operator*() const {
			return *data;
		}

		/**@brief Ritorna il puntatore al dato riferito dall'iteratore */
		pointer operator->() const {
			return data;
		}

		/**@brief Operatore di accesso random 
		 * @param index posizione a cui accedere
		 */
		reference operator[](const int index) {
			return data[index];
		}

		/**@brief post-incremento */
		u_const_iterator operator++(int) {
			u_const_iterator tmp(*this);
			++data;
			return tmp;
		}

		/**@brief pre-incremento*/
		u_const_iterator &operator++() {
			++data;
			return *this;
		}

		/**@brief post-decremento*/
		u_const_iterator operator--(int) {
			u_const_iterator tmp(*this);
			--data;
			return tmp;
		}

		/**@brief pre-decremento */
		u_const_iterator &operator--() {
			--data;
			return *this;
		}

		/**@brief Spostamentio in avanti 
		 * @param offset posizioni in avanti
		 */
		u_const_iterator operator+(int offset) {
			data += offset;
			return *this;
		}

		/**@brief Spostamentio all'indietro 
		 * @param offset posizione all'indietro
		 */
		u_const_iterator operator-(int offset) {
			data -= offset;
			return *this;
		}

		/**@brief Spostamentio in avanti della posizione 
		 * @param offset posizioni in avanti
		 */
		u_const_iterator& operator+=(int offset) {
			data += offset;
			return *this;

		}

		/**@brief Spostamentio all'indietro della posizione 
		 * @param offset posizioni all'indietro
		 */
		u_const_iterator& operator-=(int offset) {
			data -= offset;
			return *this;
		}

		/**@brief Numero di elementi tra due iteratori 
		 * @param other iteratore su cui eseguire la differenza
		 */
		difference_type operator-(const u_const_iterator &other) {
			int count = 0;
			while (this->data != other.data) {
				--data;
				count++;
			}

			return count;
		}
		/**@brief operatore di confronto
		* @param other iteratore da confrontare
		*/
		bool operator==(const u_const_iterator &other) const {
			return this->data == other.data;
		}
		/**@brief operatore di non uguaglianza
		* @param other iteratore da confrontare
		*/
		bool operator!=(const u_const_iterator &other) const {
			return this->data != other.data;
		}
		/**@brief operatore di maggiore
		* @param other iteratore da confrontare
		*/
		bool operator>(const u_const_iterator &other) const {
			return this->data > other.data;
		}
		/**@brief operatore di maggiore uguale
		* @param other iteratore da confrontare
		*/
		bool operator>=(const u_const_iterator &other) const {
			return this->data >= other.data;
		}
		/**@brief operatore di minore
		* @param other iteratore da confrontare
		*/
		bool operator<(const u_const_iterator &other) const {
			return this->data < other.data;
		}
		/**@brief operatore di minore uguale
		* @param other iteratore da confrontare
		*/
		bool operator<=(const u_const_iterator &other) const {
			return this->data <= other.data;
		}

	private:

		friend class sortedarray;
		/**@brief costruttore parametrico
		* @param v pointer a data
		*/
		u_const_iterator(const T *v) : data(v) {

		}
	}; 
	//u_const_iterator
	   /**@brief ritorna un iteratore che punta alla testa
	   */
	u_const_iterator u_begin() const {
		return u_const_iterator(uhead_);
	}
	/**@brief ritorna un iteratore che punta alla coda
	*/
	u_const_iterator u_end() const {
		return u_const_iterator(utail_+1);
	}
	class const_iterator {
		const T *posizionamento;
		const T *data;
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;
		/** @brief Costruttore Default */
		const_iterator() : posizionamento(0),data(0) {};
		/** @brief Copy constructor
		*	@param other const iterator da assegnare
		*  */
		const_iterator(const const_iterator &other) : posizionamento(other.posizionamento), data(other.data)
		{};
		/** @brief Assegnamento
		*	@param other valore const_iterator da assegnare
		*  */
		const_iterator& operator=(const const_iterator &other) {
			posizionamento = other.posizionamento;
			data = other.data;
			return *this;
		}
		/** @brief distruttore */
		~const_iterator() {
			posizionamento = 0;
			data = 0;
		};
		/** @brief dereferenziamento */
		reference operator*() {
			const int index = *posizionamento;
			return this->data[index];
		}
		/** @brief Ritorna il puntatore al dato riferito dall'iteratore */
		pointer operator->() const {
			return posizionamento;
		}
		/** @brief postincremento */
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++posizionamento;
			return tmp;
		}
		/** @brief preincremento */
		const_iterator& operator++() {
			++posizionamento;
			return *this;
		}

		/** @brief predecremento */
		const_iterator& operator--() {
			--posizionamento;
			return *this;
		}
		/** @brief postdecremento */
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			--posizionamento;
			return tmp;
		}
		/**@brief Spostamentio in avanti */
		const_iterator& operator+(int offset) {
			posizionamento += offset;
			return *this;
		}

		/**@brief Spostamentio all'indietro */
		const_iterator& operator-(int offset) {
			posizionamento -= offset;
			return *this;
		}
		/** @brief accesso a indice
		*	@param index posizione a cui accedere
		*  */
		const_iterator& operator[](const int index) {
			posizionamento = posizionamento + index;
			return *this;
		}
		/**@brief operatore di confronto
		* @param other iteratore da confrontare
		*/
		bool operator==(const const_iterator &other) const {
			return posizionamento == other.posizionamento;
		}
		/**@brief operatore di diversità
		* @param other iteratore da confrontare
		*/
		bool operator!=(const const_iterator &other) const {
			return posizionamento != other.posizionamento;
		}
		/**@brief Numero di elementi tra due iteratori
		* @param other iteratore su cui eseguire la differenza
		*/
		difference_type operator-(const u_const_iterator &other) {
			int count = 0;
			while (this->posizionamento != other.posizionamento) {
				--posizionamento;
				count++;
			}

			return count;
		}
		/**@brief operatore di minore
		* @param lhs iteratore da confrontare
		*/
		bool operator< (const const_iterator& lhs)
		{
			return this->posizionamento > lhs.posizionamento;
		};
		/**@brief operatore di maggiore
		* @param lhs iteratore da confrontare
		*/
		bool operator> (const const_iterator& lhs)
		{
			return this->posizionamento < lhs.posizionamento;
		};
		/**@brief operatore di minore uguale
		* @param lhs iteratore da confrontare
		*/
		bool operator<=(const const_iterator& lhs)
		{
			return !(this->posizionamento > lhs.posizionamento);
		}
		/**@brief operatore di maggiore uguale
		* @param lhs iteratore da confrontare
		*/
		bool operator>=(const const_iterator& lhs)
		{
			return !(this->posizionamento < lhs.posizionamento);
		}

	public:
		friend class sortedarray;
		/** @brief costruttore di default 
		* @param v pointer a array di int con le posizioni
		 */
		const_iterator(const T *v) : posizionamento(v) {}
		/**@brief costruttore che prende in input l'array delle posizioni e l'array di dati non ordinati 
		 * @param v pointer a array di int con le posizioni
		 * @param d pointer ai dati disordinati
		 */
		const_iterator(const int *v, const T* d) : posizionamento(v), data(d) {
		}

	};
	/**
	*Ritorna un const iterator che punta a testa e ha info su coda e testa
	*@brief const iterator su testa */
	const_iterator begin() const {
		return const_iterator(head_, uhead_);
	}
	/**
	*Ritorna un const iterator che punta a coda e ha info su coda e testa
	*@brief const iterator su coda */
	const_iterator end() const {
		return const_iterator(tail_+1, utail_);
	}

	//END ITERATORI
};

/**
@brief Operatore di stream

Permette di streammare il contenuto di un array in output

@param os stream di output
@param cb array da utilizzare

@return Riferimento all'output stream
**/
template <typename T,typename F>
std::ostream& operator<<(std::ostream &os, sortedarray<T,F> & cb) {
	for (int i = 0; i < cb.getLastInserted(); ++i)
		os << cb[i] << " // ";

	return os;
}

/**
@brief find_count

Funzione che permette di contare quanti elementi nella struttura dati soddisfino un predicato binario

@param SA sorted_array da valutare
@param func predicato binario
@param target valore di tipo T con il quale fare il confronto

@return count Numero di elementi che, confrontati con target, rispettano il predicato func

**/
template <typename T, typename P,typename F>
int find_count(const sortedarray<T,F> &SA, P func, const T &target) {
	int count = 0;
	for (int i = 0; i<SA.getLastInserted(); i++) {
		if (func(SA[i], target)) {
			count++;
		}
	}

	return count;
}
#endif
