#pragma once
#include <ostream>
#include <iterator>
#include <cstddef>
#include "log.h"

template <typename T, typename F>
class logicArray
{
	typedef unsigned int maxDimension;
	
	F comp_;

	unsigned int last_inserted_;

	int* head_;
	int* tail_;

	T* uhead_;
	T* utail_;
	maxDimension dimensione_array_;

	Logger logger_;
protected:
	T * unsorted_data_;
	int* sorted_data_;
public:
	//COSTRUTTORI E DISTRUTTORE
	logicArray();
	logicArray(maxDimension dimensione);
	logicArray(const logicArray &other);
	template <typename IterT>
	logicArray(IterT inizio, IterT fine, maxDimension dimensione, F comp);
	~logicArray();
	//END COSTRUTTORI E DISTRUTTORE

	//-----------------------------

	//GET E SET PARAMETRI
	T getUnsortedHead();
	T getUnsortedTail();
	// Ritorna la dimensione dell'array
	maxDimension getDimension() const;
	// Restituisce il numero di posizioni ancora libere
	int getFreeSpace() const;
	// Ritorna l'elemento in testa
	T getHead();
	// Ritorna l'elemento in coda
	T getTail();
    int getLastInserted() const;
	//END GET E SET PARAMETRI

	//-----------------------------

	//METODI E FUNZIONI
	// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
	bool insertData(const T& data);
	// Svuota l'array da tutti i dati. Svuota anche l'array delle posizioni
	bool emptyData();
	// Metodo ausiliario utilizzato nell'operatore assegnamento
	void swap(logicArray& toSwap);
	// Dispose di tutte le risorse
	bool dispose();
	// Shifta a dx di 1 posizione ogni elemento
	void shiftItem(int position) const;
	void sortedPrint();
	void unsortedPrint();
	//END METODI E FUNZIONI

	//-----------------------------

	//OPERATOR OVERLOADING
	logicArray& operator=(const logicArray &other);
	const T &operator[](maxDimension index) const;
	T &operator[](maxDimension index);
	const T &operator()(maxDimension index) const;
	T &operator()(maxDimension index);
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

		//4 metodi fondamentali
		u_const_iterator() : data(0) {}

		u_const_iterator(const u_const_iterator &other) : data(other.data) {

		}

		u_const_iterator& operator=(const u_const_iterator &other) {
			data = other.data;
			return *this;
		}

		~u_const_iterator() {
			data = 0;
		}

		//altri metodi

		//(dereferenziamento)
		reference operator*() const {
			return *data;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return data;
		}

		// Operatore di accesso random
		reference operator[](const int index) {
			return data[index];
		}

		//post-incremento
		u_const_iterator operator++(int) {
			u_const_iterator tmp(*this);
			++data;
			return tmp;
		}

		//pre-incremento
		u_const_iterator &operator++() {
			++data;
			return *this;
		}

		//post-decremento
		u_const_iterator operator--(int) {
			u_const_iterator tmp(*this);
			--data;
			return tmp;
		}

		//pre-decremento
		u_const_iterator &operator--() {
			--data;
			return *this;
		}

		//Spostamentio in avanti
		u_const_iterator operator+(int offset) {
			data += offset;
			return *this;
		}

		//Spostamentio all'indietro
		u_const_iterator operator-(int offset) {
			data -= offset;
			return *this;
		}

		// Spostamentio in avanti della posizione
		u_const_iterator& operator+=(int offset) {
			data += offset;
			return *this;

		}

		// Spostamentio all'indietro della posizione
		u_const_iterator& operator-=(int offset) {
			data -= offset;
			return *this;
		}

		// Numero di elementi tra due iteratori
		difference_type operator-(const u_const_iterator &other) {
			int count = 0;
			while (this->data != other.data) {
				--data;
				count++;
			}

			return count;
		}

		bool operator==(const u_const_iterator &other) const {
			return this->data == other.data;
		}

		bool operator!=(const u_const_iterator &other) const {
			return this->data != other.data;
		}

		bool operator>(const u_const_iterator &other) const {
			return this->data > other.data;
		}

		bool operator>=(const u_const_iterator &other) const {
			return this->data >= other.data;
		}

		bool operator<(const u_const_iterator &other) const {
			return this->data < other.data;
		}

		bool operator<=(const u_const_iterator &other) const {
			return this->data <= other.data;
		}

	private:

		friend class logicArray;

		u_const_iterator(const T *v) : data(v) {

		}
	}; //u_const_iterator

	u_const_iterator u_begin() const {
		return u_const_iterator(uhead_);
	}

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
		// Ritorna il puntatore al dato riferito dall'iteratore
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
		//Spostamentio in avanti
		const_iterator& operator+(int offset) {
			posizionamento += offset;
			return *this;
		}

		//Spostamentio all'indietro
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
		/** @brief confronto */
		bool operator==(const const_iterator &other) const {
			return posizionamento == other.posizionamento;
		}
		/** @brief diversità */
		bool operator!=(const const_iterator &other) const {
			return posizionamento != other.posizionamento;
		}
		difference_type operator-(const u_const_iterator &other) {
			int count = 0;
			while (this->posizionamento != other.posizionamento) {
				--posizionamento;
				count++;
			}

			return count;
		}
		bool operator< (const const_iterator& lhs)
		{
			return this->posizionamento > lhs.posizionamento;
		};
		bool operator> (const const_iterator& lhs)
		{
			return this->posizionamento < lhs.posizionamento;
		};
		bool operator<=(const const_iterator& lhs)
		{
			return !(this->posizionamento > lhs.posizionamento);
		}
		bool operator>=(const const_iterator& lhs)
		{
			return !(this->posizionamento < lhs.posizionamento);
		}

	public:
		friend class logicArray;
		/** @brief costruttore di default */
		const_iterator(const T *v) : posizionamento(v) {}
		const_iterator(const int *v, const T* d) : posizionamento(v), data(d) {
		}
		/** @brief costruttore con info su testa e coda */
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

template <typename T,typename F>
std::ostream& operator<<(std::ostream &os, logicArray<T,F> & cb) {
	for (int i = 0; i < cb.getLastInserted(); ++i)
		os << cb[i] << " // ";

	return os;
}

template <typename T, typename P,typename F>
int find_count(const logicArray<T,F> &la, P func, const T &target) {
	int count = 0;
	for (int i = 0; i<la.getLastInserted(); i++) {
		if (func(la[i], target)) {
			count++;
		}
	}

	return count;
}