#include "logicArray.cpp"
struct greterInt {
	bool operator() (const int a,const int b) {
		return a > b;
	}
};
void genericTest();
void iteratorTest();
int main()
{
	genericTest();
	iteratorTest();
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

	//assert(testbuffer.get_dimensione() == 5 && testbuffer.get_spazioLibero() == 0);
	cout << "Size: " << testbuffer.getDimension() << " , spazio libero: " << testbuffer.getFreeSpace() << std::endl;

	//logger.log(Logger::INFO, "Su circularbuffer di stringhe");

	//string s[6] = {
	//	"aa",
	//	"bb",
	//	"cc",
	//	"dd",
	//	"ee",
	//	"ff"
	//};

	//logicArray<string> testbuffer2(s, s + 6, 6,ord);
	//cout << testbuffer2 << std::endl;
	////assert(testbuffer2.get_dimensione() == 6 && testbuffer2.get_spazioLibero() == 0);

	//cout << "Size: " << testbuffer2.getDimension() << " , spazio libero: " << testbuffer2.getFreeSpace() << std::endl;
	//
	//circularbuffer<int>::const_iterator p, pe;
}