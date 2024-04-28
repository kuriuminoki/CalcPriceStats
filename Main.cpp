#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "CsvReader.h"
#include "CalcUnit.h"


using namespace std;


void calcAndPrint(Calculator* calculator) {
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

	// 入力を読み込む
	CsvReader* reader;
	reader = new CsvReader(path.c_str());

	// 計算し標準出力
	Calculator* calculator;
	calculator = new Calculator(reader);
	calcAndPrint(calculator);

	delete reader;
	delete calculator;

}