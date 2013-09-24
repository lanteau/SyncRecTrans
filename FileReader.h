/* FileReader class
*
*	FileReader object takes a filename in it's constructor. This file is then read
* into an internal string using the Parse() method. A string containing the
* the file's data can be obtained with GetFileString(). A vector of Messages
* can also be obtained with GetMessages().
*
* Author: Logan Anteau
*/

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

	FileReader(std::string fileName);

	//Changes FileReader to look at a new file
	void ChangeFile(std::string fileName);

	//Reads the input file into m_fileData
	void Parse();

	//Returns string containing contents of file
	std::string GetFileString();

	FileReader::MessageVec GetMessages();

};

#endif /* FILEREADER_H */