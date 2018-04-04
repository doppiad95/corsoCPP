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
void test_count();
void test_iteratori2();
void test_iteratori();
int main()
{
	genericTest();
	iteratorTest();
	test_complex();
	test_inizio_fine();
	test_count();
	test_iteratori2();
	test_iteratori();
}
void genericTest()
{
	logicArray<int,greterInt> logicarray(10);
	logicarray.insertData(1);
	logicarray.insertData(10);
	logicarray.insertData(4);
	logicarray.insertData(2);
	logicarray.insertData(7);
	/*logicarray.sortedPrint();
	logicarray.unsortedPrint();*/
	logicarray.insertData(1);
	//logicarray.sortedPrint();
	//logicarray.unsortedPrint();
	logicarray.insertData(6);
	logicarray.insertData(3);
	logicarray.insertData(11);
	logicarray.insertData(0);
	logicarray.sortedPrint();
	logicarray.unsortedPrint();
	cout << logicarray(3) << "\n";
	cout << logicarray[3] << "\n";
	logicarray.emptyData();
	logicarray.insertData(10);
	logicarray.insertData(2);
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

	logicArray<int,greterInt> testbuffer(a, a + 5, 5, ord);

	logger.log(Logger::INFO, "Su circularbuffer di interi in circularbuffer di char");
	logicArray<char,greterInt> testbuffer1(a, a + 5, 5, ord);

	cout << testbuffer << std::endl;
	cout << testbuffer1 << std::endl;
	int *p = std::find(a, a + 5, 72);
	if (p <= a + 5)
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
	logicArray<string,greaterString> testbuffer2(s, s + 6, 6, gs);
	cout << testbuffer2 << std::endl;
	//assert(testbuffer2.get_dimensione() == 6 && testbuffer2.get_spazioLibero() == 0);

	cout << "Size: " << testbuffer2.getDimension() << " , spazio libero: " << testbuffer2.getFreeSpace() << std::endl;

	logicArray<string,greaterString>::const_iterator px, pe;
}
inline void test_complex() {
	complex com;
	logicArray<complex,complex> testbuffer(5);
	Logger logger(Logger::ALL);
	logger.log(Logger::INFO, "Insertimento dei seguenti numeri complessi (1,1), (1,2), (2,7), (0,0), (5,4)");
	testbuffer.insertData(complex(1, 1));
	testbuffer.insertData(complex(1, 2));
	testbuffer.insertData(complex(2, 7));
	testbuffer.insertData(complex(0, 0));
	testbuffer.insertData(complex(5, 4));

	logger.log(Logger::INFO, "------ Test stampa con operator <<");
	cout << testbuffer << std::endl;

	logger.log(Logger::INFO, "------ Test stampa con operator << dopo cancellamento testa");
	cout << testbuffer << std::endl;

	cout << "Dimensione della lista dopo cancellamento testa: " << testbuffer.getLastInserted() << std::endl;

}
void test_inizio_fine() {
	Logger logger(Logger::ALL);
	logger.log(Logger::INFO, "----- Test scrittura con const_iterator");
	logicArray<int,greterInt> testbuffer(5);
	greterInt g;
	testbuffer.insertData(44);
	testbuffer.insertData(61);
	testbuffer.insertData(91);
	testbuffer.insertData(11);
	testbuffer.insertData(411);
	logicArray<int,greterInt>::const_iterator iw = testbuffer.begin();

	logicArray<int,greterInt>::const_iterator i = testbuffer.begin();
	logicArray<int,greterInt>::const_iterator ie = testbuffer.end();
	cout << std::endl;
	for (; iw != ie; iw++) {
		cout << *iw << "-";
	}

	logger.log(Logger::INFO, " ---- Test lettura/scrittura con iterator");

	logicArray<int, greterInt>::unsorted_const_iterator ui = testbuffer.u_begin();
	logicArray<int, greterInt>::unsorted_const_iterator uie = testbuffer.u_end();
	cout << "Unsorted" << std::endl;
	for (; ui != uie; ui++) {
		cout << *ui << "-";
	}
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
struct equal {
	bool operator() (const int a, const int b) {
		return a == b;
	}
};

void test_count() {
	std::cout << "Test sul metodo test_count()" << std::endl;
	equal func;
	logicArray<int,greterInt> a(5);
	a.insertData(2);
	a.insertData(1);
	a.insertData(2);
	a.insertData(3);
	a.insertData(2);

	std::cout << find_count(a, func, 2) << std::endl;

}
void test_iteratori() {
	logicArray<int, greterInt>::unsorted_const_iterator ib, ie, iw, ir, is;

	logicArray<int, greterInt> a(5);

	a.insertData(5);
	a.insertData(1);
	a.insertData(-2);
	a.insertData(3);
	a.insertData(4);

	ib = a.u_begin();
	ie = a.u_end();

	iw = ib;
	ir = ib;



	std::cout << *ir << std::endl;
	std::cout << *(ir += 2) << std::endl;
	std::cout << *(ir - 1) << std::endl;
	std::cout << ir[3] << std::endl;

	for (; ib != ie; ++ib) {
		std::cout << *ib << " ";
	}

	std::cout << std::endl;
}

//8

void test_iteratori2() {
	logicArray<int, greterInt>::const_iterator ib, ie, iw, ir, is;

	logicArray<int, greterInt> a(5);

	a.insertData(5);
	a.insertData(1);
	a.insertData(-2);
	a.insertData(3);
	a.insertData(4);

	ib = a.begin();
	ie = a.end();

	iw = ib;
	ir = ib;
	iw++;
	iw++;

	is = iw;

	//std::cout << *(is + 1) << std::endl;
	std::cout << (ib > ie) << std::endl;
	std::cout << (ib >= ie) << std::endl;
	std::cout << (ib < ie) << std::endl;
	std::cout << (ib <= ie) << std::endl;




}