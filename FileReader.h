#ifndef FILEREADER_H
#define FILEREADER_H

#include "Message.h"
#include <string>
#include <vector>

class FileReader
{
	std::string m_fileName;
	std::string m_fileData;

	typedef std::vector<Message> MessageVec;

public:

	FileReader();
	FileReader(std::string fileName);

	//Returns string containing contents of file
	std::string GetFileString();
	FileReader::MessageVec GetMessages();

	//Changes FileReader to look at a new file
	void ChangeFile(std::string fileName);
	//Reads the input file into m_fileData
	void Parse();
};

#endif /* FILEREADER_H */