#ifndef _TYPEUNIONDEFINE_H
#define _TYPEUNIONDEFINE_H

union Int8Union {
	bool b;
	char byte;
	char sBuff[sizeof(char)];
};

union ShortUnion {
	short s;
	char sBuff[sizeof(short)];
};
union IntUnion {
	int s;
	char sBuff[sizeof(int)];
};
union LongUnion {
	long long s;
	char sBuff[sizeof(long long)];
};
union FloatUnion {
	float f;
	char fBuff[sizeof(float)];
};
union DoubleUnion {
	double d;
	char dBuff[sizeof(double)];
};
#endif