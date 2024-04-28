#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "CsvReader.h"
#include "CalcUnit.h"


using namespace std;


void test(CsvReader* reader) {
	string name = "�a��������I�����i8��";
	map<string, string> test = reader->findOne("INPUT1:", "Name", name.c_str());

	string value = test["�o��"];

	cout << value << endl;
}


void calcTest(Calculator* calculator) {
	cout << "�o�ׂP�@: " << round(calculator->shipping1()) << endl;
	cout << "�o�ׂQ�@: " << round(calculator->shipping2()) << endl;
	cout << "�o�׍��v: " << round(calculator->shippingSum()) << endl;
	cout << "���X�P�@: " << round(calculator->loss1()) << endl;
	cout << "���X�Q�@: " << round(calculator->loss2()) << endl;
	cout << "���X���v: " << round(calculator->lossSum()) << endl;
	cout << "����@�@: " << round(calculator->income()) << endl;
	cout << "�ō��@�@: " << round(calculator->incomeWithTax()) << endl;
	cout << "�q���@�@: " << round(calculator->customer()) << endl;
	cout << "�q�P�@�@: " << round(calculator->incomePerCustomer()) << endl;
	cout << "���X�@�@: " << round(calculator->allLoss()) << endl;
	cout << "���X���@: " << round(calculator->lossRate()) << endl;
	cout << "��΁@�@: " << round(calculator->comparaLastYear()) << endl;
}


int main() {

	string dirName;
	cout << "�t�H���_������́F" << flush;
	cin >> dirName;
	string path = "resources/" + dirName + "/input.csv";

	CsvReader* reader;
	reader = new CsvReader(path.c_str());

	Calculator* calculator;
	calculator = new Calculator(reader);

	calcTest(calculator);

	delete reader;

}