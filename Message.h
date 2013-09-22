#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message
{
	std::string m_rawMessage; // contains actual message plus extra control characters, etc
	std::string m_data;

	int m_dataLen; // length of data in message
	int m_fLen; // length of data + control characters 

	bool m_valid;

public:
	Message(std::string data);
	Message(unsigned char* buffer, int len);

	int GetDataLength();
	int GetFrameLength();
	// Returns true if byte is verified by odd parity check
	bool isValid();
	std::string GetDataString();
	std::string GetRawString();


private:
	void Frame();
	void DeFrame();
	void Verify();

	bool CalculateOddParity(unsigned char byte);

};


#endif /* MESSAGE_H */

