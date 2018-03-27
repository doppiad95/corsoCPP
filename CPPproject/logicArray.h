#pragma once
#include "log.h"
template <typename T>
class logicArray
{
	typedef unsigned int maxDimension;
	T *unsortedData;
	int lastInserted;
	int sortedData[];
	T* _head;
	T* _tail;
	maxDimension _dimensioneArray;
	Logger logger;
public:
	logicArray();
	logicArray(const maxDimension dimensione);
	~logicArray();

	// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
	bool insertData(const T& data);

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


};

