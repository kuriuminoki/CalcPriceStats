#include "CsvReader.h"

#include <fstream>
#include <sstream>


using namespace std;


// ��s���̃e�L�X�g�����s���̃f�[�^�ɕϊ�
vector<string> csv2vector(string buff) {
	vector<string> data;
	string oneCell = "";

	// 1���������Ă���
	for (int i = 0; buff[i] != '\0'; i++) {
		// CSV�t�@�C���Ȃ̂ŃJ���}�ŋ�؂���oneData��push_back
		if (buff[i] == ',') {
			data.push_back(oneCell);
			oneCell = "";
		}
		else { // �J���}�ȊO�̕����Ȃ獇��
			oneCell += buff[i];
		}
	}
	// �Ō�̃Z���ɂ̓J���}���Ȃ�
	data.push_back(oneCell);

	return data;
}


// �t�@�C�������w�肵��CSV�t�@�C����ǂݍ���
CsvReader::CsvReader(const char* fileName) {

	// �o�b�t�@
	string line;

	// �t�@�C�����J��
	ifstream ifs(fileName);

	// �ŏ��̈�s�ڂ͎̂Ă�
	getline(ifs, line);

	string domainName = "";
	// �t�@�C���̏I�[�܂Ń��[�v
	while (getline(ifs, line)) {

		// ��s���̃e�L�X�g���f�[�^�ɂ���Vector�ɕϊ�
		vector<string> oneDataVector = csv2vector(line);

		if ((oneDataVector[1] == "" && oneDataVector[0].find(":") != std::string::npos)) {
			domainName = oneDataVector[0];
			getline(ifs, line);
			m_columnNames[domainName] = csv2vector(line);
		}
		else {
			// vector�ƃJ���������g����map�𐶐�
			map<string, string> oneData;
			for (int i = 0; i < oneDataVector.size(); i++) {
				oneData[m_columnNames[domainName][i]] = oneDataVector[i];
			}

			// ��s����map�f�[�^��push_back
			m_data[domainName].push_back(oneData);
		}
	}

	// �t�@�C�������
	ifs.close();
}


/*
* �h���C������domainName�̃f�[�^����A
* �J��������value�̃f�[�^���擾
* ��FfindOne("DOMAIN:", "name", "value");
* ������Ȃ��������̃f�[�^��Ԃ�
*/
map<string, string> CsvReader::findOne(const char* domainName, const char* columnName, const char* value) {

	// m_data[i][columnName] == value�ƂȂ�i�𒲂ׂ�
	map<string, string>::iterator ite;

	vector<map<string, string> > data = m_data[domainName];

	for (int i = 0; i < data.size(); i++) {

		// �J�������ɑΉ�����l���擾
		ite = data[i].find(columnName);

		// ���̃J�����������݂��Ȃ�
		if (ite == data[i].end()) { continue; }

		// �����Ɉ�v
		if (ite->second == value) {
			return data[i];
		}
	}

	// ��̃f�[�^��Ԃ�
	map<string, string> res;
	return res;
}


