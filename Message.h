#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>

class Message
{
	std::string m_rawMessage; // contains actual message plus extra control characters, etc
	std::string m_data;

	std::vector<std::string> m_blocks;
	int m_dataLen; // length of data in message

	bool m_valid;

public:
	Message(std::string data);
	Message(unsigned char* buffer, int len);

	int GetLength();
	int GetNumBlocks();
	std::vector<std::string> GetBlocks();
	// Returns true if byte is verified by odd parity check
	bool isValid();
	std::string GetDataString();


private:
	void Frame();
	void DeFrame();
	void Verify();

	bool CalculateOddParity(unsigned char byte);

};


#endif /* MESSAGE_H */

