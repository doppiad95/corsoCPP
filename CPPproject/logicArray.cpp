#include "logicArray.h"
template <typename T, typename F>
logicArray<T,F>::logicArray(const maxDimension dimensione) : last_inserted_(0), head_(0), tail_(0), uhead_(0), utail_(0), dimensione_array_(0), logger_(Logger::WARNING), unsorted_data_(0), sorted_data_(0)
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
template <typename T, typename F>
logicArray<T, F>::logicArray(const logicArray &other) :last_inserted_(0), head_(0), tail_(0), uhead_(0), utail_(0), dimensione_array_(0), logger_(Logger::WARNING), unsorted_data_(0), sorted_data_(0)
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



template <typename T, typename F>
logicArray<T, F>::logicArray() : last_inserted_(0), head_(0), tail_(0), uhead_(0), utail_(0), dimensione_array_(0), logger_(Logger::WARNING), unsorted_data_(0), sorted_data_(0)
{
}
template <typename T, typename F>
logicArray<T, F>::~logicArray()
{
	if (!dispose())
		logger_.log(Logger::ERROR, "Impossibile eseguire il dispose delle risorse. Possibili memory leak");
}
template<typename T, typename F>
template<typename  IterT>
logicArray<T,F>::logicArray(IterT inizio, IterT fine, const maxDimension dimensione, F comp) : last_inserted_(0),head_(0), tail_(0)
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

template <typename T,typename F>
// Inserimento di dati nell'array non ordinato e inserimento della posizione nell'array che tiene traccia dell'ordine
bool logicArray<T,F>::insertData(const T& data)
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

// Svuota l'array da tutti i dati. Svuota anche l'array delle posizioni
template<typename T,typename  F>
bool logicArray<T,F>::emptyData()
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

// Ritorna la dimensione dell'array
template<typename T, typename  F >
unsigned int logicArray<T,F>::getDimension() const
{
	return this->dimensione_array_;
}

// Restituisce il numero di posizioni ancora libere
template<typename T, typename  F >
int logicArray<T,F>::getFreeSpace() const
{
	return this->dimensione_array_ - this->last_inserted_ > 0 ? this->dimensione_array_ - this->last_inserted_ : 0;
}

// Ritorna l'elemento in testa
template<typename T, typename  F>
T logicArray<T,F>::getHead()
{
	return this->head_;
}

// Ritorna l'elemento in coda
template<typename T, typename  F>
T logicArray<T,F>::getTail()
{
	return this->tail_;
}

// Metodo ausiliario utilizzato nell'operatore assegnamento
template<typename T, typename  F >
void logicArray<T,F>::swap(logicArray& to_swap)
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

// Dispose di tutte le risorse
template<typename T, typename  F>
bool logicArray<T,F>::dispose()
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

// Shifta a dx di 1 posizione ogni elemento
template<typename T, typename  F >
void logicArray<T,F>::shiftItem(int position) const
{
	int temp = sorted_data_[getDimension() - 1];
	for (unsigned int i = position; i < getDimension(); i++) {
		const int temp1 = sorted_data_[i];
		sorted_data_[i] = temp;
		temp = temp1;
	}
	cout << std::endl;
}

template<typename T, typename  F>
void logicArray<T,F>::sortedPrint()
{
	std::cout << "SORTED PRINT\n";
	for (unsigned int i = 0; i < last_inserted_; i++)
		std::cout << "Posizione:\t" << sorted_data_[i] << "\tValore:\t" << unsorted_data_[sorted_data_[i]] << "\n";
	std::cout << "---------- END SORTED PRINT-----------------\n";
}

template<typename T, typename  F>
void logicArray<T,F>::unsortedPrint()
{
	std::cout << "----------- UNSORTED PRINT ------------\n";
	for (unsigned int i = 0; i < last_inserted_; i++)
		std::cout << "Posizione:\t" << i << "\tValore:\t" << unsorted_data_[i] << "\n";
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
	return unsorted_data_[sorted_data_[index]];
}

template<typename T, typename  F >
T & logicArray<T,F>::operator[](const maxDimension index)
{
	return unsorted_data_[sorted_data_[index]];
}
template<typename T, typename  F>
const T & logicArray<T,F>::operator()(const maxDimension index) const
{
	return unsorted_data_[index];
}

template<typename T, typename  F>
T & logicArray<T,F>::operator()(const maxDimension index)
{
	return unsorted_data_[index];
}

template<typename T, typename  F>
T logicArray<T,F>::getUnsortedHead()
{
	return uhead_;
}

template<typename T, typename  F>
T logicArray<T,F>::getUnsortedTail()
{
	return utail_;
}
template<typename T, typename  F>
int logicArray<T,F>::getLastInserted() const
{
	return last_inserted_;
}
