#include "CsvReader.h"

#include <fstream>
#include <sstream>


using namespace std;


// 一行分のテキストから一行分のデータに変換
vector<string> csv2vector(string buff) {
	vector<string> data;
	string oneCell = "";

	// 1文字ずつ見ていく
	for (int i = 0; buff[i] != '\0'; i++) {
		// CSVファイルなのでカンマで区切ってoneDataにpush_back
		if (buff[i] == ',') {
			data.push_back(oneCell);
			oneCell = "";
		}
		else { // カンマ以外の文字なら合体
			oneCell += buff[i];
		}
	}
	// 最後のセルにはカンマがない
	data.push_back(oneCell);

	return data;
}


// ファイル名を指定してCSVファイルを読み込む
CsvReader::CsvReader(const char* fileName) {

	// バッファ
	string line;

	// ファイルを開く
	ifstream ifs(fileName);

	// 最初の一行目は捨てる
	getline(ifs, line);

	string domainName = "";
	// ファイルの終端までループ
	while (getline(ifs, line)) {

		// 一行分のテキストをデータにしてVectorに変換
		vector<string> oneDataVector = csv2vector(line);

		if ((oneDataVector[1] == "" && oneDataVector[0].find(":") != std::string::npos)) {
			domainName = oneDataVector[0];
			getline(ifs, line);
			m_columnNames[domainName] = csv2vector(line);
		}
		else {
			// vectorとカラム名を使ってmapを生成
			map<string, string> oneData;
			for (int i = 0; i < oneDataVector.size(); i++) {
				oneData[m_columnNames[domainName][i]] = oneDataVector[i];
			}

			// 一行分のmapデータをpush_back
			m_data[domainName].push_back(oneData);
		}
	}

	// ファイルを閉じる
	ifs.close();
}


/*
* ドメイン名がdomainNameのデータから、
* カラム名がvalueのデータを取得
* 例：findOne("DOMAIN:", "name", "value");
* 見つからなかったら空のデータを返す
*/
map<string, string> CsvReader::findOne(const char* domainName, const char* columnName, const char* value) {

	// m_data[i][columnName] == valueとなるiを調べる
	map<string, string>::iterator ite;

	vector<map<string, string> > data = m_data[domainName];

	for (int i = 0; i < data.size(); i++) {

		// カラム名に対応する値を取得
		ite = data[i].find(columnName);

		// そのカラム名が存在しない
		if (ite == data[i].end()) { continue; }

		// 条件に一致
		if (ite->second == value) {
			return data[i];
		}
	}

	// 空のデータを返す
	map<string, string> res;
	return res;
}


