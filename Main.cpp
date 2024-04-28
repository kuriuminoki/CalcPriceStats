#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

#include "CsvReader.h"
#include "CalcUnit.h"


using namespace std;


void calcAndPrint(Calculator* calculator) {
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

	// ���͂�ǂݍ���
	CsvReader* reader;
	reader = new CsvReader(path.c_str());

	// �v�Z���W���o��
	Calculator* calculator;
	calculator = new Calculator(reader);
	calcAndPrint(calculator);

	delete reader;
	delete calculator;

}