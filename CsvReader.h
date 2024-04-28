#ifndef CSV_READER_H_INCLUDED
#define CSV_READER_H_INCLUDED

#include <vector>
#include <string>
#include <map>


class CsvReader {
private:
	/*
	* データ
	* m_data[行番号]<カラム名, データ>
	*/
	std::map<std::string, std::vector<std::map<std::string, std::string> > > m_data;

	/*
	* カラム名のリスト
	*/
	std::map<std::string, std::vector<std::string> > m_columnNames;

public:
	// ファイル名を指定してCSVファイルを読み込む
	CsvReader(const char* fileName);

	/*
	* ドメイン名がdomainNameのデータから、
	* カラム名がvalueのデータを取得
	* 例：findOne("Character", "Name", "キャラ名");
	*/
	std::map<std::string, std::string> findOne(const char* domainName, const char* columnName, const char* value);

	std::vector<std::map<std::string, std::string> > getDomainData(const char* domainName) { return m_data[domainName]; }

};

#endif