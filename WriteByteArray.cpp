#include "WriteByteArray.h"
#include "TypeUnionDefine.h"
#include <stdio.h>
#define _CRT_SECURE_DEPRECATE_MEMORY
#include <memory.h>
WriteByteArray::WriteByteArray(int default_size) :
m_curindex(0), m_pBuffer(0), m_size(default_size)
{
	if (m_size > 0)
	{
		m_pBuffer = new char[m_size];
		memset(m_pBuffer, 0, m_size);
	}
}
WriteByteArray::WriteByteArray(const WriteByteArray& wb)
{
	const char* src = wb.getBuffer(m_size);
	m_pBuffer = new char[m_size];
	memcpy(m_pBuffer, src, m_size);
	m_curindex = m_size;
}
WriteByteArray::~WriteByteArray()
{
	if (m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}
bool WriteByteArray:: write(const char* lpBuffer, int Length)
{
	if (Length <= 0)
	{
		return false;
	}
	while (isOverflow(Length))
	{
		resize();
	}
	memcpy(m_pBuffer + m_curindex, lpBuffer, Length);
	m_curindex += Length;
	return true;
}
bool WriteByteArray::isOverflow(int Length)
{
	return (Length >= (m_size - m_curindex));
}
void WriteByteArray::resize()
{
	//当前缓存大小
	int prevBuferSize = m_size;
	//扩大一倍
	m_size <<= 1;
	//申请缓存
	char *pNewData = new char[m_size];
	memset(pNewData, 0, m_size);
	//拷贝到新缓存
	memcpy(pNewData, m_pBuffer, prevBuferSize);
	delete[] m_pBuffer;
	m_pBuffer = pNewData;
}
void WriteByteArray::clearData()
{
	memset(m_pBuffer, 0, m_size);
	m_curindex = 0;
}
const char* WriteByteArray::getBuffer(int& len) const
{
	len = m_curindex;
	return m_pBuffer;
}
bool WriteByteArray::writeBool(bool b)
{
	char c = b ? 1 : 0;
	return writeInt8(c);
}
bool WriteByteArray::writeInt8(char n)
{
	return write((const char*)&n, sizeof(char));
}
//bool WriteByteArray::writeInt8(unsigned char n)
//{
//	return write((const char*)&n, sizeof(unsigned char));
//}
bool WriteByteArray::writeInt16(short n)
{
	ShortUnion myunion;
#ifdef LITTLE_ENDIAN
	myunion.s = n;
#else
	myunion.sBuff[0] = (n & 0xFF00) >> 8;
	myunion.sBuff[1] = (n & 0x00FF);
#endif
	return write(myunion.sBuff, sizeof(short));
}
//bool WriteByteArray::writeInt16(unsigned short n)
//{
//	char data[2] = { 0 };
//	data[0] = (n & 0xFF00) >> 8;
//	data[1] = (n & 0x00FF);
//	return write(data, sizeof(unsigned short));
//}
bool WriteByteArray::writeInt32(int n)
{
	IntUnion myunion;
#ifdef LITTLE_ENDIAN
	myunion.s = n;
#else
	myunion.sBuff[0] = (n & 0xFF000000) >> 24;
	myunion.sBuff[1] = (n & 0x00FF0000) >> 16;
	myunion.sBuff[2] = (n & 0x0000FF00) >> 8;
	myunion.sBuff[3] = (n & 0x000000FF);
#endif
	return write(myunion.sBuff, sizeof(int));
}
//bool WriteByteArray::writeInt32(unsigned int n)
//{
//	char data[4] = { 0 };
//	data[0] = (n & 0xFF000000) >> 24;
//	data[1] = (n & 0x00FF0000) >> 16;
//	data[2] = (n & 0x0000FF00) >> 8;
//	data[3] = (n & 0x000000FF);
//	return write(data, sizeof(unsigned int));
//}
bool WriteByteArray::writeInt64(long long n)
{
	LongUnion myunion;
#ifdef LITTLE_ENDIAN
	myunion.s = n;
#else
	myunion.sBuff[0] = (n & 0xFF00000000000000) >> 56;
	myunion.sBuff[1] = (n & 0x00FF000000000000) >> 48;
	myunion.sBuff[2] = (n & 0x0000FF0000000000) >> 40;
	myunion.sBuff[3] = (n & 0x000000FF00000000) >> 32;
	myunion.sBuff[4] = (n & 0x00000000FF000000) >> 24;
	myunion.sBuff[5] = (n & 0x0000000000FF0000) >> 16;
	myunion.sBuff[6] = (n & 0x000000000000FF00) >> 8;
	myunion.sBuff[7] = (n & 0x00000000000000FF);
#endif
	return write(myunion.sBuff, sizeof(long long));
}
//bool WriteByteArray::writeInt64(unsigned long long n)
//{
//	return write((const char*)&n, sizeof(unsigned long long));
//}
bool WriteByteArray::writeFloat(float n)
{
	FloatUnion myunion;
	myunion.f = n;
#ifdef LITTLE_ENDIAN
	return write(myunion.fBuff, sizeof(float));
#else
	int size = sizeof(float);
	char data[sizeof(float)] = { 0 };
	for (int i = 0; i < size; i++)
	{
		data[i] = myunion.fBuff[size - i - 1];
	}
	return write(data, size);
#endif
}
bool WriteByteArray::writeDouble(double n)
{
	DoubleUnion myunion;
	myunion.d = n;
#ifdef LITTLE_ENDIAN
	return write(myunion.dBuff, sizeof(double));
#else
	int size = sizeof(double);
	char data[sizeof(double)] = { 0 };
	for (int i = 0; i < size; i++)
	{
		data[i] = myunion.dBuff[size - i - 1];
	}
	return write(data, size);
#endif
}
bool WriteByteArray::writeUTF(const char* utf, int len)
{
	writeInt16((short)len);
	return write(utf, len);
}
