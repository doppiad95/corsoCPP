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
	//COSTRUTTORI E DISTRUTTORE
	logicArray();
	logicArray(const maxDimension dimensione);
	logicArray(const logicArray &other);
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
};
