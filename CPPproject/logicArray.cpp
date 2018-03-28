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
template<typename T>
logicArray<T>::logicArray(const logicArray &other) :unsortedData(0), sortedData(0), lastInserted(0), _head(0), _tail(0), _uhead(0), _utail(0), _dimensioneArray(0), logger(Logger::WARNING)
{
	unsortedData = new T[other._dimensioneArray];
	sortedData = new int[other._dimensioneArray];

	lastInserted = other.lastInserted;

	_head = other._head;
	_tail = other._tail;

	_uhead = other._uhead;
	_utail = other._utail;

	_dimensioneArray = other._dimensioneArray;
	try {
		for (int i = 0; i < _dimensioneArray; i++)
		{
			unsortedData[i] = other.unsortedData[i];
			sortedData[i] = other.sortedData[i];
		}
	}catch(...)
	{
		logger.log(Logger::ERROR, "Impossibile usare il copyconstructor");
		dispose();
	}
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

template <typename T>
template <typename F>
// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
bool logicArray<T>::insertData(const T& data, F comp)
{
	unsortedData[lastInserted] = data;
	bool inserito = false;
		int i = 0;
		for (i = 0; i < lastInserted; i++)
		{
			if (!comp(data, unsortedData[sortedData[i]]))
			{
				shiftItem(i);
				sortedData[i] = lastInserted;
				inserito = true;
			}
		}
		if (!inserito)
			sortedData[i] = lastInserted;
		lastInserted++;
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

// Shifta a dx di 1 posizione ogni elemento
template<typename T>
void logicArray<T>::shiftItem(int position)
{
	int temp = sortedData[getDimension() - 1];
	     for (int i = position; i < getDimension(); i++) {
	         int temp1 = sortedData[i];
	         sortedData[i] = temp;
	         temp = temp1;
			 cout << sortedData[i] << " ";
	
	}
	 cout << std::endl;
}

template<typename T>
void logicArray<T>::sortedPrint()
{
	std::cout << "SORTED PRINT\n";
	for (int i = 0; i < lastInserted; i++)
		std::cout << "Posizione:\t" << i << "\tValore:\t" << unsortedData[sortedData[i]]<<"\n";
	std::cout << "---------- END SORTED PRINT-----------------\n";
}

template<typename T>
void logicArray<T>::unsortedPrint()
{
	for (int i = 0; i < lastInserted; i++)
		std::cout << "Posizione:\t" << i << "\tValore:\t" << unsortedData[i]<<"\n";

}
