#pragma once
#include "log.h"
template <typename T>
class logicArray
{
	typedef unsigned int maxDimension;
	T *unsortedData;
	int* sortedData;

	int lastInserted;

	T* _head;
	T* _tail;

	T* _uhead;
	T* _utail;
	maxDimension _dimensioneArray;

	Logger logger;
public:
	logicArray();
	logicArray(const maxDimension dimensione);
	logicArray(const logicArray &other);
	~logicArray();

	// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
	template<typename F>
	bool insertData(const T& data, F comp);

	// Svuota l'array da tutti i dati. Svuota anche l'array delle posizioni
	bool emptyData();
	// Ritorna la dimensione dell'array
	maxDimension getDimension();
	// Restituisce il numero di posizioni ancora libere
	int getFreeSpace();
	// Ritorna l'elemento in testa
	T getHead();
	// Ritorna l'elemento in coda
	T getTail();
	// Metodo ausiliario utilizzato nell'operatore assegnamento
	void swap(logicArray& toSwap);
	// Dispose di tutte le risorse
	bool dispose();


	// Shifta a dx di 1 posizione ogni elemento
	void shiftItem(int position);
	void sortedPrint();
	void unsortedPrint();
	logicArray& operator=(const logicArray &other);
	const T &operator[](const maxDimension index) const;
	T &operator[](const maxDimension index);
	const T &operator()(const maxDimension index) const;
	T &operator()(const maxDimension index);
	T getUnsortedHead();
	T getUnsortedTail();
};

