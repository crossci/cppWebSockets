#include "ReadByteArray.h"
#include "TypeUnionDefine.h"
ReadByteArray::ReadByteArray(const char* src, int len) :m_src(src),
m_curindex(0), m_len(len)
{}
std::string ReadByteArray::readUTF()
{
	int len = readInt16();
	if (len > 0)
	{
		char* data = new char[len+1];
		memset(data, 0, len + 1);
		memcpy(data, m_src + m_curindex, len);
		m_curindex += len;
		std::string ret(data);
		delete[] data;
		return ret;
	}
	return "";
}
bool ReadByteArray::readBool()
{
	if (m_curindex < m_len)
	{
		Int8Union myunion;
		memcpy(myunion.sBuff, m_src + m_curindex, 1);
		++m_curindex;
		return myunion.b;
	}
	return false;
}
short ReadByteArray::readInt8()
{
	if (m_curindex < m_len)
	{
		Int8Union myunion;
		memcpy(myunion.sBuff, m_src + m_curindex, 1);
		++m_curindex;
		return myunion.byte;
	}
	return 0;
}
short ReadByteArray::readInt16()
{
#ifdef LITTLE_ENDIAN
	if (m_curindex < m_len)
	{
		ShortUnion myunion;
		memcpy(myunion.sBuff, m_src + m_curindex, 2);
		m_curindex += 2;
		return myunion.s;
	}
#else
	if (m_curindex < m_len)
	{
		unsigned char data[2] = { 0 };
		memcpy(&data, m_src + m_curindex, 2);
		m_curindex += 2;
		short ret = (data[0] & 0xFF) << 8 | data[1];
		return ret;
	}
#endif
	return 0;
}

int ReadByteArray::readInt32()
{
#ifdef LITTLE_ENDIAN
	if (m_curindex < m_len)
	{
		IntUnion myunion;
		int size = sizeof(float);
		memcpy(myunion.sBuff, m_src + m_curindex, size);
		m_curindex += size;
		return myunion.s;
	}
#else
	if (m_curindex < m_len)
	{
		unsigned char data[4] = { 0 };
		memcpy(&data, m_src + m_curindex, 4);
		m_curindex += 4;
		int ret = (data[0] & 0xFF) << 24 |
			(data[1] & 0xFF) << 16 |
			(data[2] & 0xFF) << 8 |
			data[3];
		return ret;
	}
#endif
	return 0;
}
float ReadByteArray:: readFloat()
{
#ifdef LITTLE_ENDIAN
	if (m_curindex < m_len)
	{
		FloatUnion myUnion;
		int size = sizeof(float);
		memcpy(myUnion.fBuff, m_src + m_curindex, size);
		m_curindex += size;
		return myUnion.f;
	}
#else
	if (m_curindex < m_len)
	{
		FloatUnion myUnion;
		int size = sizeof(float);
		for (int i = 0; i < size; i++)
		{
			myUnion.fBuff[i] = *(m_src + m_curindex + size - i - 1);
		}
		m_curindex += size;
		return myUnion.f;
	}
#endif
	return 0;
}
double ReadByteArray::readDouble()
{
#ifdef LITTLE_ENDIAN
	if (m_curindex < m_len)
	{
		DoubleUnion myUnion;
		int size = sizeof(double);
		memcpy(myUnion.dBuff, m_src + m_curindex, size);
		m_curindex += size;
		return myUnion.d;
	}
#else
	if (m_curindex < m_len)
	{
		DoubleUnion myUnion;
		int size = sizeof(double);
		for (int i = 0; i < size; i++)
		{
			myUnion.dBuff[i] = *(m_src + m_curindex + i);
		}
		m_curindex += size;
		return myUnion.d;
	}
#endif
	return 0;
}
void ReadByteArray::rewind()
{
	m_curindex = 0;
}
void ReadByteArray::set(const char* src, int len)
{
	m_src = src;
	m_len = len;
	m_curindex = 0;
}