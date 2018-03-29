#include "logicArray.cpp"
struct greterInt {
	bool operator() (const int a,const int b) {
		return a > b;
	}
};
int main()
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
