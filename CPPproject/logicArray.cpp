#include "logicArray.h"


template <typename T>
logicArray<T>::logicArray(const maxDimension dimensione) : unsortedData(0), sortedData(0), lastInserted(0),_head(0),_tail(0),_uhead(0),_utail(0),_dimensioneArray(0),logger(Logger::WARNING)
{
	_dimensioneArray = dimensione;
	unsortedData = new T[dimensione];
	sortedData = new int[dimensione];
	
	_head = &sortedData[0];
	_tail = &sortedData[0];

	_uhead = &unsortedData[0];
	_utail = &unsortedData[0];
	
	lastInserted = 0;
}
template <typename T>
logicArray<T>::logicArray() : unsortedData(0), sortedData(0), lastInserted(0), _head(0), _tail(0), _uhead(0), _utail(0), _dimensioneArray(0), logger(Logger::WARNING)
{

}
template <typename T>
logicArray<T>::~logicArray()
{
	if (!dispose())
		logger.log(Logger::ERROR, "Impossibile eseguire il dispose delle risorse. Possibili memory leak");
}

// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
template<typename T>
bool logicArray<T>::insertData(const T& data)
{
	return false;
}

// Svuota l'array da tutti i dati. Svuota anche l'array delle posizioni
template<typename T>
bool logicArray<T>::emptyData()
{
	logger.log(Logger::INFO, "Inizio procedura di svuotamento");
	lastInserted = 0;
	T* current = _head;
	int pos = 0;
	while (current != _tail) {
		*current = 0;
		sortedData[pos] = 0;
		current++;
		pos++;
	}
	_tail = _head;
	logger.log(Logger::INFO, "Fine procedura di svuotamento");
    return true;
}


// Ritorna la dimensione dell'array
template<typename T>
unsigned int logicArray<T>::getDimension()
{
	return this->_dimensioneArray;
}

// Restituisce il numero di posizioni ancora libere
template<typename T>
int logicArray<T>::getFreeSpace()
{
	return this->_dimensioneArray - this->lastInserted > 0 ? this->_dimensioneArray - this->lastInserted : 0;
}

// Ritorna l'elemento in testa
template<typename T>
T logicArray<T>::getHead()
{
	return this->_head;
}

// Ritorna l'elemento in coda
template<typename T>
T logicArray<T>::getTail()
{
	return this->_tail;
}

// Metodo ausiliario utilizzato nell'operatore assegnamento
template<typename T>
void logicArray<T>::swap(logicArray& toSwap)
{
	std::swap(toSwap.lastInserted, this->lastInserted);
	std::swap(toSwap.unsortedData, this->unsortedData);
	std::swap(toSwap._dimensioneArray, this->_dimensioneArray);
	std::swap(toSwap._head, this->_head);
	std::swap(toSwap._tail, this->_tail);
	std::swap(toSwap.sortedData, this->sortedData);
}

// Dispose di tutte le risorse
template<typename T>
bool logicArray<T>::dispose()
{
	try {
		logger.log(Logger::WARNING, "Inizio dispose delle risorse");
		delete[] unsortedData;
		delete[] sortedData;
		lastInserted = 0;
		_head = 0;
		_tail = 0;
		_dimensioneArray = 0;
		logger.log(Logger::WARNING, "Fine dispose delle risorse");
	}
	catch (...)
	{
		return false;
	}
		return true;
}
