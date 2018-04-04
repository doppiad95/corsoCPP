#include "logicArray.h"

template <typename T, typename F>
logicArray<T,F>::logicArray(const maxDimension dimensione) : unsortedData(0), sortedData(0), lastInserted(0), _head(0), _tail(0), _uhead(0), _utail(0), _dimensioneArray(0), logger(Logger::WARNING)
{
	try {
		_dimensioneArray = dimensione;
		unsortedData = new T[dimensione];
		sortedData = new int[dimensione];

		_head = &sortedData[0];
		_tail = &sortedData[0];

		_uhead = &unsortedData[0];
		_utail = &unsortedData[0];

		lastInserted = 0;
	}
	catch (std::exception& e) {
		std::cerr << "exception caught: " << e.what() << '\n';
	}
}
template <typename T, typename F>
logicArray<T, F>::logicArray(const logicArray &other) :unsortedData(0), sortedData(0), lastInserted(0), _head(0), _tail(0), _uhead(0), _utail(0), _dimensioneArray(0), logger(Logger::WARNING)
{
	unsortedData = new T[other._dimensioneArray];
	sortedData = new int[other._dimensioneArray];

	lastInserted = other.lastInserted;

	_head = other._head;
	_tail = other._tail;

	_uhead = other._uhead;
	_utail = other._utail;

	_dimensioneArray = other._dimensioneArray;
	comp = other.comp;
	try {
		for (int i = 0; i < _dimensioneArray; i++)
		{
			unsortedData[i] = other.unsortedData[i];
			sortedData[i] = other.sortedData[i];
		}
	}
	catch (...)
	{
		logger.log(Logger::ERROR, "Impossibile usare il copyconstructor");
		dispose();
	}
}



template <typename T, typename F>
logicArray<T, F>::logicArray() : unsortedData(0), sortedData(0), lastInserted(0), _head(0), _tail(0), _uhead(0), _utail(0), _dimensioneArray(0), logger(Logger::WARNING)
{
}
template <typename T, typename F>
logicArray<T, F>::~logicArray()
{
	if (!dispose())
		logger.log(Logger::ERROR, "Impossibile eseguire il dispose delle risorse. Possibili memory leak");
}
template<typename T, typename F>
template<typename  IterT>
logicArray<T,F>::logicArray(IterT inizio, IterT fine, const maxDimension dimensione, F comp) : lastInserted(0)
{
	_dimensioneArray = dimensione;
	unsortedData = new T[dimensione];
	sortedData = new int[dimensione];
	try
	{
		for (; inizio != fine; ++inizio)
			insertData(static_cast<T>(*inizio));
	}
	catch (std::invalid_argument e)
	{
		cout << e.what() << std::endl;
	}
	catch (std::out_of_range e)
	{
		cout << e.what() << std::endl;
	}
	catch (...)
	{
		logger.log(Logger::ERROR, "Eccezione sconosciuta sollevata riga 52, cbuffer.h");
	}
}

template <typename T,typename F>
// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
bool logicArray<T,F>::insertData(const T& data)
{
	if (lastInserted == _dimensioneArray)
		throw new std::out_of_range("Array pieno, impossibile inserire ulteriori elementi");
	try {
		unsortedData[lastInserted] = data;
		bool inserito = false;
		int i = 0;
		for (i = 0; i < lastInserted; i++)
		{
			if (!comp(data, unsortedData[sortedData[i]]) && !inserito)
			{
				shiftItem(i);
				sortedData[i] = lastInserted;
				inserito = true;
			}
		}
		if (!inserito)
			sortedData[i] = lastInserted;
		_tail = &sortedData[lastInserted];
		_utail = &unsortedData[lastInserted];
		lastInserted++;
	}
	catch (std::exception& e) {
		std::cerr << "exception caught: " << e.what() << '\n';
		return false;
	}
	return true;
}

// Svuota l'array da tutti i dati. Svuota anche l'array delle posizioni
template<typename T,typename  F>
bool logicArray<T,F>::emptyData()
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
template<typename T, typename  F >
unsigned int logicArray<T,F>::getDimension() const
{
	return this->_dimensioneArray;
}

// Restituisce il numero di posizioni ancora libere
template<typename T, typename  F >
int logicArray<T,F>::getFreeSpace()
{
	return this->_dimensioneArray - this->lastInserted > 0 ? this->_dimensioneArray - this->lastInserted : 0;
}

// Ritorna l'elemento in testa
template<typename T, typename  F>
T logicArray<T,F>::getHead()
{
	return this->_head;
}

// Ritorna l'elemento in coda
template<typename T, typename  F>
T logicArray<T,F>::getTail()
{
	return this->_tail;
}

// Metodo ausiliario utilizzato nell'operatore assegnamento
template<typename T, typename  F >
void logicArray<T,F>::swap(logicArray& toSwap)
{
	try {
		std::swap(toSwap.lastInserted, this->lastInserted);
		std::swap(toSwap.unsortedData, this->unsortedData);
		std::swap(toSwap._dimensioneArray, this->_dimensioneArray);
		std::swap(toSwap._head, this->_head);
		std::swap(toSwap._tail, this->_tail);
		std::swap(toSwap.sortedData, this->sortedData);
	}
	catch (std::exception& e) {
		std::cerr << "exception caught: " << e.what() << '\n';
	}
}

// Dispose di tutte le risorse
template<typename T, typename  F>
bool logicArray<T,F>::dispose()
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
template<typename T, typename  F >
void logicArray<T,F>::shiftItem(int position)
{
	int temp = sortedData[getDimension() - 1];
	for (unsigned int i = position; i < getDimension(); i++) {
		int temp1 = sortedData[i];
		sortedData[i] = temp;
		temp = temp1;
	}
	cout << std::endl;
}

template<typename T, typename  F>
void logicArray<T,F>::sortedPrint()
{
	std::cout << "SORTED PRINT\n";
	for (int i = 0; i < lastInserted; i++)
		std::cout << "Posizione:\t" << i << "\tValore:\t" << unsortedData[sortedData[i]] << "\n";
	std::cout << "---------- END SORTED PRINT-----------------\n";
}

template<typename T, typename  F>
void logicArray<T,F>::unsortedPrint()
{
	std::cout << "----------- UNSORTED PRINT ------------\n";
	for (int i = 0; i < lastInserted; i++)
		std::cout << "Posizione:\t" << i << "\tValore:\t" << unsortedData[i] << "\n";
	std::cout << "---------- END UNSORTED PRINT-----------------\n";
}

template <typename T, typename  F>
logicArray<T,F>& logicArray<T,F>::operator=(const logicArray& other)
{
	if (this != other)
	{
		logicArray tmp(other);
		this->swap(tmp);
	}
	return *this;
}

template<typename T, typename  F>
const T & logicArray<T,F>::operator[](const maxDimension index) const
{
	return unsortedData[sortedData[index]];
}

template<typename T, typename  F >
T & logicArray<T,F>::operator[](const maxDimension index)
{
	return unsortedData[sortedData[index]];
}
template<typename T, typename  F>
const T & logicArray<T,F>::operator()(const maxDimension index) const
{
	return unsortedData[index];
}

template<typename T, typename  F>
T & logicArray<T,F>::operator()(const maxDimension index)
{
	return unsortedData[index];
}

template<typename T, typename  F>
T logicArray<T,F>::getUnsortedHead()
{
	return _uhead;
}

template<typename T, typename  F>
T logicArray<T,F>::getUnsortedTail()
{
	return _utail;
}
template<typename T, typename  F>
int logicArray<T,F>::getLastInserted() const
{
	return lastInserted;
}