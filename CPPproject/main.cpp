#include "logicArray.cpp"
struct greterInt {
	bool operator() (const int a, const int b) {
		return a > b;
	}
};
struct greaterString {
	bool operator() (const string a, const string b) {
		return a[0] > b[0];
	}
};
struct complex {
	int real; ///< coordinata x del punto
	int imm; ///< coordinata y del punto
	complex() : real(0), imm(0) {}
	complex(int xx, int yy) : real(xx), imm(yy) {}
	bool operator() (const complex a, const complex b) {
		if (a.real != b.real)
			return a.real > b.real;
		else
			return a.imm > b.imm;
	}
};
std::ostream &operator<<(std::ostream &os, const complex &p) {
	os << "(" << p.real << ", " << p.imm << "i)";

	return os;
}
void genericTest();
void test_complex();
void iteratorTest();
void test_inizio_fine();
int main()
{
	genericTest();
	iteratorTest();
	test_complex();
	test_inizio_fine();
}
void genericTest()
{
	logicArray<int> logicarray(10);
	greterInt ord;
	logicarray.insertData(1, ord);
	logicarray.insertData(10, ord);
	logicarray.insertData(4, ord);
	logicarray.insertData(2, ord);
	logicarray.insertData(7, ord);
	/*logicarray.sortedPrint();
	logicarray.unsortedPrint();*/
	logicarray.insertData(1, ord);
	//logicarray.sortedPrint();
	//logicarray.unsortedPrint();
	logicarray.insertData(6, ord);
	logicarray.insertData(3, ord);
	logicarray.insertData(11, ord);
	logicarray.insertData(0, ord);
	logicarray.sortedPrint();
	logicarray.unsortedPrint();
	cout << logicarray(3) << "\n";
	cout << logicarray[3] << "\n";
	logicarray.emptyData();
	logicarray.insertData(10, ord);
	logicarray.insertData(2, ord);
	logicarray.sortedPrint();
	logicarray.unsortedPrint();
}
void iteratorTest()
{
	greterInt ord;
	Logger logger(Logger::ALL);
	logger.log(Logger::INFO, "-----Test costruzione e stampa buffer costruito con iteratori");
	logger.log(Logger::INFO, "Su circularbuffer di interi");
	int a[5] = { 67, 90 ,72, 82, 81 };

	logicArray<int> testbuffer(a, a + 5, 5, ord);

	logger.log(Logger::INFO, "Su circularbuffer di interi in circularbuffer di char");
	logicArray<char> testbuffer1(a, a + 5, 5, ord);

	cout << testbuffer << std::endl;
	cout << testbuffer1 << std::endl;
	int *p = std::find(a, a + 5, 72);
	if (p != a + 5)
		std::cout << "Element found in myints: " << *p << '\n';
	else
		std::cout << "Element not found in myints\n";
	//assert(testbuffer.get_dimensione() == 5 && testbuffer.get_spazioLibero() == 0);
	cout << "Size: " << testbuffer.getDimension() << " , spazio libero: " << testbuffer.getFreeSpace() << std::endl;

	logger.log(Logger::INFO, "Su circularbuffer di stringhe");

	string s[6] = {
		"dd",
		"ee",
		"ff",
		"aa",
		"bb",
		"cc"
	};
	greaterString gs;
	logicArray<string> testbuffer2(s, s + 6, 6, gs);
	cout << testbuffer2 << std::endl;
	//assert(testbuffer2.get_dimensione() == 6 && testbuffer2.get_spazioLibero() == 0);

	cout << "Size: " << testbuffer2.getDimension() << " , spazio libero: " << testbuffer2.getFreeSpace() << std::endl;

	logicArray<string>::const_iterator px, pe;
}
inline void test_complex() {
	logicArray<complex> testbuffer(5);
	Logger logger(Logger::ALL);
	complex com;
	logger.log(Logger::INFO, "Insertimento dei seguenti numeri complessi (1,1), (1,2), (2,7), (0,0), (5,4)");
	testbuffer.insertData(complex(1, 1), com);
	testbuffer.insertData(complex(1, 2), com);
	testbuffer.insertData(complex(2, 7), com);
	testbuffer.insertData(complex(0, 0), com);
	testbuffer.insertData(complex(5, 4), com);

	logger.log(Logger::INFO, "------ Test stampa con operator <<");
	cout << testbuffer << std::endl;

	logger.log(Logger::INFO, "------ Test stampa con operator << dopo cancellamento testa");
	cout << testbuffer << std::endl;

	cout << "Dimensione della lista dopo cancellamento testa: " << testbuffer.getLastInserted() << std::endl;

	complex c[6] = { complex(1,1), complex(2,4), complex(1,5), complex(3,4), complex(6,8), complex(5,2) };

	logicArray<complex> testbuffer2(c, c + 6, 6, com);

	cout << testbuffer2 << std::endl;
}
void test_inizio_fine() {
	Logger logger(Logger::ALL);
	greterInt ord;
	logger.log(Logger::INFO, "----- Test scrittura con const_iterator");
	logicArray<int> testbuffer(5);

	testbuffer.insertData(44, ord);
	testbuffer.insertData(61, ord);
	testbuffer.insertData(91, ord);
	testbuffer.insertData(11, ord);
	testbuffer.insertData(411, ord);

	logicArray<int>::const_iterator iw = testbuffer.begin();

	logicArray<int>::const_iterator i = testbuffer.begin();
	logicArray<int>::const_iterator ie = testbuffer.end();
	cout << std::endl;
	for (; iw != ie; ++iw) {
		cout << *iw << "-";
	}

	cout << *iw << std::endl;

	logger.log(Logger::INFO, " ---- Test lettura/scrittura con iterator");

	/*logicArray<int>::iterator i1 = testbuffer.begin();
	logicArray<int>::iterator iw1 = testbuffer.begin();
	const logicArray<int>::iterator ie1 = testbuffer.end();

	logger.log(Logger::INFO, "La sequenza era 4,6,9,1,41. Provo a modificare 91 con 5, poi stampo");

	++iw1;
	++iw1;
	int a = 5;
	iw1[0] = a;

	for (; i1 != ie1; ++i1) {
		cout << *i1 << " ";
	}

	cout << *i1 << std::endl;*/
}