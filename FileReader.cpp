#include "FileReader.h"
#include <fstream>
#include <string>
#include <cerrno>

FileReader::FileReader(std::string fileName) :
	m_fileName(fileName)
{
}

void FileReader::ChangeFile(std::string fileName)
{
	m_fileName = fileName;
	m_fileData.empty();
}

void FileReader::Parse()
{
	std::ifstream in(m_fileName.c_str(), std::ios::in | std::ios::binary);

	if(in)
	{
		in.seekg(0, std::ios::end);
		m_fileData.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&m_fileData[0], m_fileData.size());
		in.close();

	}
	else
		throw(errno);
}

std::string FileReader::GetFileString()
{
	return m_fileData;
}

FileReader::MessageVec FileReader::GetMessages()
{
	MessageVec messages;
	int dataPos = 0;

	//Calc number of frames
	int numFrames = m_fileData.length() / 64;
	if(m_fileData.length() % 64 > 0)
		numFrames++;

	for(int i = 0; i < numFrames; i++)
	{
		//Calculate length of frame
		int frameLen = 64;
		if(dataPos+64 > m_fileData.length())
			frameLen = m_fileData.length() - dataPos;

		std::string newMessageStr = m_fileData.substr(dataPos, frameLen);
		Message msg(newMessageStr);
		messages.push_back(msg);

		dataPos += frameLen;
	}

	return messages;
}