/* Message class
*
*	A Message object represents a single "block" of data in our protocol. Each Message
* starts with 2 ASCII SYN characters, then a byte representing length of the data to
* follow (1-64 bytes). Finally, the data itself that is between 1 and 64 bytes in
* length
*
* Author: Logan Anteau
*/

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