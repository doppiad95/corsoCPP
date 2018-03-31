#pragma once
#include <iostream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cstddef>
#include "log.h"

template <typename T>
class logicArray
{
	typedef unsigned int maxDimension;

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
	template <typename IterT, typename F>
	logicArray(IterT inizio, IterT fine, const maxDimension dimensione, F comp);
	~logicArray();
	//END COSTRUTTORI E DISTRUTTORE

	//-----------------------------

	//GET E SET PARAMETRI
	T getUnsortedHead();
	T getUnsortedTail();
	// Ritorna la dimensione dell'array
	maxDimension getDimension();
	// Restituisce il numero di posizioni ancora libere
	int getFreeSpace();
	// Ritorna l'elemento in testa
	T getHead();
	// Ritorna l'elemento in coda
	T getTail();
	int getLastInserted();
	//END GET E SET PARAMETRI

	//-----------------------------

	//METODI E FUNZIONI
	// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
	template<typename F>
	bool insertData(const T& data, F comp);
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
		const_iterator() : posizionamento() {};
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
		/** @brief assegnamento da const iterator */
		const_iterator& operator=(const iterator &other) {
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
			return &(posizionamento->unsortedData[sortedData]);
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
			iterator tmp(*this);
			--posizionamento;
			return tmp;
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
		bool operator< (const iterator& lhs) { return this.posizionamento > lhs.posizionamento; }
		bool operator> (const iterator& lhs) { return this.posizionamento < lhs.posizionamento; }
		bool operator<=(const iterator& lhs) { return !(this.posizionamento > lhs.posizionamento); }
		bool operator>=(const iterator& lhs) { return !(this.posizionamento < lhs.posizionamento); }

		friend class iterator;
		/** @brief confronto */
		bool operator==(const iterator &other) const {
			return posizionamento == other.posizionamento;
		}
		/** @brief diversità */
		bool operator!=(const iterator &other) const {
			return posizionamento != other.posizionamento;
		}
		/** @brief copycostruttore con iterator */
		const_iterator(const iterator &other) {
			this->posizionamento = other.posizionamento;
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
		return const_iterator(_tail, _utail);
	}

	//END ITERATORI
};

template <typename T>
std::ostream& operator<<(std::ostream &os, logicArray<T> & cb) {
	for (int i = 0; i < cb.getLastInserted(); ++i)
		os << cb[i] << " // ";

	return os;
}
