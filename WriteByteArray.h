#ifndef _WRITEBYTEARRAY_H
#define _WRITEBYTEARRAY_H
class WriteByteArray
{
public:
	WriteByteArray(int default_size=128);
	WriteByteArray(const WriteByteArray&);
	~WriteByteArray();
	bool write(const char* lpBuffer, int Length);
	bool isOverflow(int Length);
	void resize();
	void clearData();
	const char* getBuffer(int& len) const;
	bool writeBool(bool b);
	bool writeInt8(char n);
	//bool writeInt8(unsigned char n);
	bool writeInt16(short n);
	//bool writeInt16(unsigned short n);
	bool writeInt32(int n);
	//bool writeInt32(unsigned int n);
	bool writeInt64(long long n);
	//bool writeInt64(unsigned long long n);
	bool writeFloat(float n);
	bool writeDouble(double n);
	bool writeUTF(const char* utf,int len);
public:
	int m_size;
	int m_curindex;
	char* m_pBuffer;
};
#endif