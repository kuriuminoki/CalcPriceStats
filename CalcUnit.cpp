#include "CalcUnit.h"
#include "CsvReader.h"


#include <map>
#include <vector>


using namespace std;


Calculator::Calculator(CsvReader* reader) {
	m_reader = reader;
	m_priceMapping = new CsvReader("resources/priceMapping.csv");
}

Calculator::~Calculator() {
	delete m_priceMapping;
}


// 特殊な変換が必要な場合priceMapping.csvに記載の価格を返す
double Calculator::mapPrice(const char* name, const char* num, double price) {
	map<string, string> valueStr = m_priceMapping->findOne("MAP:", "Name", name);
	if (valueStr.size() == 0) { return price; }
	return stod(valueStr[num]);
}


// Price×[指定した列]の合計を計算
double Calculator::calcPriceMultiSum(const char* domainName, const char* columnName) {
	double shipping = 0;
	vector<map<string, string> > data = m_reader->getDomainData(domainName);
	for (unsigned int i = 0; i < data.size(); i++) {
		double price = stod(data[i]["Price"]);
		if ((bool)stoi(data[i]["gramFlag"])) {
			price /= 100.0;
		}
		string num = data[i][columnName];
		price *= stod(num);
		price = mapPrice(data[i]["Name"].c_str(), num.c_str(), price);
		shipping += price;
	}
	return shipping;
}


/*
* 各項目の計算
*/
double Calculator::shipping1() {
	return calcPriceMultiSum("INPUT1:", "出荷");
}
double Calculator::shipping2() {
	return calcPriceMultiSum("INPUT2:", "出荷");
}
double Calculator::shippingSum() {
	return shipping1() + shipping2();
}
double Calculator::loss1() {
	return calcPriceMultiSum("INPUT1:", "ロス");
}
double Calculator::loss2() {
	return calcPriceMultiSum("INPUT2:", "ロス");
}
double Calculator::lossSum() {
	return loss1() + loss2();
}
double Calculator::income() {
	vector<map<string, string> > data = m_reader->getDomainData("COMMON:");
	double allIncome = stod(data[0]["売上(全)"]);
	double directOrderIncome = stod(data[0]["直注"]) / TAX_RATE;
	return allIncome - directOrderIncome;
}
double Calculator::incomeWithTax() {
	return income() * TAX_RATE;
}
double Calculator::customer() {
	return stod(m_reader->getDomainData("COMMON:")[0]["客数"]);
}
double Calculator::incomePerCustomer() {
	return income() / customer();
}
double Calculator::allLoss() {
	return lossSum();
}
double Calculator::lossRate() {
	return allLoss() / shippingSum() * 100;
}
double Calculator::comparaLastYear() {
	double incomeOfLastYear = stod(m_reader->getDomainData("COMMON:")[0]["昨年売上"]);
	return incomeWithTax() / incomeOfLastYear * 100;
}