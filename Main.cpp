#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "CsvReader.h"
#include "CalcUnit.h"


using namespace std;


void test(CsvReader* reader) {
	string name = "和牛入り特選肉寿司8貫";
	map<string, string> test = reader->findOne("INPUT1:", "Name", name.c_str());

	string value = test["出荷"];

	cout << value << endl;
}


void calcTest(Calculator* calculator) {
	cout << "出荷１　: " << round(calculator->shipping1()) << endl;
	cout << "出荷２　: " << round(calculator->shipping2()) << endl;
	cout << "出荷合計: " << round(calculator->shippingSum()) << endl;
	cout << "ロス１　: " << round(calculator->loss1()) << endl;
	cout << "ロス２　: " << round(calculator->loss2()) << endl;
	cout << "ロス合計: " << round(calculator->lossSum()) << endl;
	cout << "売上　　: " << round(calculator->income()) << endl;
	cout << "税込　　: " << round(calculator->incomeWithTax()) << endl;
	cout << "客数　　: " << round(calculator->customer()) << endl;
	cout << "客単　　: " << round(calculator->incomePerCustomer()) << endl;
	cout << "ロス　　: " << round(calculator->allLoss()) << endl;
	cout << "ロス率　: " << round(calculator->lossRate()) << endl;
	cout << "昨対　　: " << round(calculator->comparaLastYear()) << endl;
}


int main() {

	string dirName;
	cout << "フォルダ名を入力：" << flush;
	cin >> dirName;
	string path = "resources/" + dirName + "/input.csv";

	CsvReader* reader;
	reader = new CsvReader(path.c_str());

	Calculator* calculator;
	calculator = new Calculator(reader);

	calcTest(calculator);

	delete reader;

}