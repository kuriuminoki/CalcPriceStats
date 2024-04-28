#ifndef CSV_READER_H_INCLUDED
#define CSV_READER_H_INCLUDED

#include <vector>
#include <string>
#include <map>


class CsvReader {
private:
	/*
	* �f�[�^
	* m_data[�s�ԍ�]<�J������, �f�[�^>
	*/
	std::map<std::string, std::vector<std::map<std::string, std::string> > > m_data;

	/*
	* �J�������̃��X�g
	*/
	std::map<std::string, std::vector<std::string> > m_columnNames;

public:
	// �t�@�C�������w�肵��CSV�t�@�C����ǂݍ���
	CsvReader(const char* fileName);

	/*
	* �h���C������domainName�̃f�[�^����A
	* �J��������value�̃f�[�^���擾
	* ��FfindOne("Character", "Name", "�L������");
	*/
	std::map<std::string, std::string> findOne(const char* domainName, const char* columnName, const char* value);

	std::vector<std::map<std::string, std::string> > getDomainData(const char* domainName) { return m_data[domainName]; }

};

#endif