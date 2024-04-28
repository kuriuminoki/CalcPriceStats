#ifndef CSV_CALC_UNIT_H_INCLUDED
#define CSV_CALC_UNIT_H_INCLUDED


class CsvReader;


class Calculator {

private:

	const double TAX_RATE = 1.08;

	CsvReader* m_reader;

	CsvReader* m_priceMapping;

public:

	Calculator(CsvReader* reader);
	~Calculator();

	// äeçÄñ⁄ÇÃåvéZ
	double shipping1();
	double shipping2();
	double shippingSum();
	double loss1();
	double loss2();
	double lossSum();
	double income();
	double incomeWithTax();
	double customer();
	double incomePerCustomer();
	double allLoss();
	double lossRate();
	double comparaLastYear();

private:

	double mapPrice(const char* name, const char* num, double price);

	double calcPriceMultiSum(const char* domainName, const char* columnName);

};

#endif