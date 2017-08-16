#ifndef _READBYTEARRAY_H
#define _READBYTEARRAY_H
#include <string>
class ReadByteArray
{
public:
	ReadByteArray(const char* src, int len);
	std::string readUTF();
	bool readBool();
	short readInt8();
	short readInt16();
	int readInt32();
	float readFloat();
	double readDouble();
	void rewind();
	void set(const char* src, int len);
public:
	const char* m_src;
	int m_curindex;
	int m_len;
};

#endif