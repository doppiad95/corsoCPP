#pragma once
#include <iostream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cstddef>
#include "log.h"

template <typename T, typename F>
class logicArray
{
	typedef unsigned int maxDimension;
	
	F comp;

	int lastInserted;

	int* _head;
	int* _tail;

	T* _uhead;
	T* _utail;
	maxDimension _dimensioneArray;

	Logger logger;
protected:
	T * unsortedData;
	int* sortedData;
public:
	//COSTRUTTORI E DISTRUTTORE
	logicArray();
	logicArray(const maxDimension dimensione);
	logicArray(const logicArray &other);
	template <typename IterT>
	logicArray(IterT inizio, IterT fine, const maxDimension dimensione, F comp);
	~logicArray();
	//END COSTRUTTORI E DISTRUTTORE

	//-----------------------------

	//GET E SET PARAMETRI
	T getUnsortedHead();
	T getUnsortedTail();
	// Ritorna la dimensione dell'array
	maxDimension getDimension() const;
	// Restituisce il numero di posizioni ancora libere
	int getFreeSpace();
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
	void shiftItem(int position);
	void sortedPrint();
	void unsortedPrint();
	//END METODI E FUNZIONI

	//-----------------------------

	//OPERATOR OVERLOADING
	logicArray& operator=(const logicArray &other);
	const T &operator[](const maxDimension index) const;
	T &operator[](const maxDimension index);
	const T &operator()(const maxDimension index) const;
	T &operator()(const maxDimension index);
	//END OPERATOR OVERLOADING

	//ITERATORI
	class const_iterator;
	class unsorted_const_iterator {
		const T *posizionamento;
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                        value_type;
		typedef ptrdiff_t                difference_type;
		typedef const T*                 pointer;
		typedef const T&                 reference;

		//4 metodi fondamentali
		unsorted_const_iterator() : posizionamento(0) {}

		unsorted_const_iterator(const unsorted_const_iterator &other) : posizionamento(other.posizionamento) {

		}

		unsorted_const_iterator& operator=(const unsorted_const_iterator &other) {
			posizionamento = other.posizionamento;
			return *this;
		}

		~unsorted_const_iterator() {

		}

		//altri metodi

		//(dereferenziamento)
		reference operator*() const {
			return *posizionamento;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return posizionamento;
		}

		// Operatore di accesso random
		reference operator[](int index) {
			return posizionamento[index];
		}

		//post-incremento
		unsorted_const_iterator operator++(int) {
			unsorted_const_iterator tmp(*this);
			++posizionamento;
			return tmp;
		}

		//pre-incremento
		unsorted_const_iterator &operator++() {
			++posizionamento;
			return *this;
		}

		//post-decremento
		unsorted_const_iterator operator--(int) {
			unsorted_const_iterator tmp(*this);
			--posizionamento;
			return tmp;
		}

		//pre-decremento
		unsorted_const_iterator &operator--() {
			--posizionamento;
			return *this;
		}

		//Spostamentio in avanti
		unsorted_const_iterator operator+(int offset) {
			return this->posizionamento + offset;
		}

		//Spostamentio all'indietro
		unsorted_const_iterator operator-(int offset) {
			return this->posizionamento - offset;
		}

		// Spostamentio in avanti della posizione
		unsorted_const_iterator& operator+=(int offset) {
			posizionamento += offset;
			return *this;

		}

		// Spostamentio all'indietro della posizione
		unsorted_const_iterator& operator-=(int offset) {
			posizionamento -= offset;
			return *this;
		}

		// Numero di elementi tra due iteratori
		difference_type operator-(const unsorted_const_iterator &other) {
			int count = 0;
			while (this->posizionamento != other.posizionamento) {
				--posizionamento;
				count++;
			}

			return count;
		}

		bool operator==(const unsorted_const_iterator &other) const {
			return this->posizionamento == other.posizionamento;
		}

		bool operator!=(const unsorted_const_iterator &other) const {
			return this->posizionamento != other.posizionamento;
		}

		bool operator>(const unsorted_const_iterator &other) const {
			return this->posizionamento > other.posizionamento;
		}

		bool operator>=(const unsorted_const_iterator &other) const {
			return this->posizionamento >= other.posizionamento;
		}

		bool operator<(const unsorted_const_iterator &other) const {
			return this->posizionamento < other.posizionamento;
		}

		bool operator<=(const unsorted_const_iterator &other) const {
			return this->posizionamento <= other.posizionamento;
		}

	private:

		friend class logicArray;

		unsorted_const_iterator(const T *v) : posizionamento(v) {

		}
	}; //unsorted_const_iterator

	unsorted_const_iterator u_begin() const {
		return unsorted_const_iterator(_uhead);
	}

	unsorted_const_iterator u_end() const {
		return unsorted_const_iterator(_utail+1);
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
		const_iterator() : posizionamento(0) {};
		/** @brief Copy constructor
		*	@param other const iterator da assegnare
		*  */
		const_iterator(const const_iterator &other) : posizionamento(other.posizionamento)
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
		};
		/** @brief dereferenziamento */
		reference operator*() {
			int index = *posizionamento;
			return data[index];
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
		const_iterator operator+(int offset) {
			return (this->posizionamento + offset);
		}

		//Spostamentio all'indietro
		const_iterator operator-(int offset) {
			return this->posizionamento - offset;
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
		difference_type operator-(const unsorted_const_iterator &other) {
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
		return const_iterator(_head, _uhead);
	}
	/**
	*Ritorna un const iterator che punta a coda e ha info su coda e testa
	*@brief const iterator su coda */
	const_iterator end() const {
		return const_iterator(_tail+1, _utail);
	}

	//END ITERATORI
};

template <typename T,typename F>
std::ostream& operator<<(std::ostream &os, logicArray<T,F> & cb) {
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
int find_count(const logicArray<T,F> &SA, P func, const T &target) {
	int count = 0;
	for (int i = 0; i<SA.getLastInserted(); i++) {
		if (func(SA[i], target)) {
			count++;
		}
	}

	return count;
}