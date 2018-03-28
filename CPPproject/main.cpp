#include "logicArray.cpp"
struct greterInt {
	bool operator() (const int a,const int b) {
		return a > b;
	}
};
int main()
{
	logicArray<int> logicarray(5);
	greterInt ord;
	logicarray.insertData(1, ord);
	logicarray.insertData(2, ord);
	logicarray.insertData(3, ord);
	logicarray.insertData(5, ord);
	logicarray.insertData(4, ord);
	logicarray.sortedPrint();
	logicarray.unsortedPrint();
}
