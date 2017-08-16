#include "WebServer.h"
#include "ReadByteArray.h"
#include "WriteByteArray.h"
void WebServer::onConnect(int socketID)
{
	string log1 = "onConnect ";
}
void WebServer::onMessage(struct lws *wsi, void* in, int len)
{
	if (in != nullptr && len > 0)
	{
		const char* inData = (const char*)in;
		ReadByteArray ba(inData, len);
		std::string str = ba.readUTF();
		int int32 = ba.readInt32();
		int int16 = ba.readInt16();
		double double1 = ba.readDouble();
		bool bool1 = ba.readBool();
		bool bool2 = ba.readBool();
		bool bool3 = ba.readBool();
		int int8 = ba.readInt8();
		cout << str << endl;
		cout << int32 << endl;
		cout << int16 << endl;
		cout << double1 << endl;
		cout << bool1 << endl;
		cout << bool2 << endl;
		cout << bool3 << endl;
		cout << int8 << endl;
		cout << endl;
		WriteByteArray* wb = new WriteByteArray(1);
		wb->writeUTF(str.c_str(),str.length());
		wb->writeInt32(int32);
		wb->writeInt16(int16);
		wb->writeDouble(double1);
		wb->writeBool(bool1);
		wb->writeBool(bool2);
		wb->writeBool(bool3);
		wb->writeInt8(int8);
		int len1 = 0;
		const char* wb_data = wb->getBuffer(len1);
		ba.set(wb_data, len1);

		std::string str1 = ba.readUTF();
		int int321 = ba.readInt32();
		int int161 = ba.readInt16();
		double double11 = ba.readDouble();
		bool bool11 = ba.readBool();
		bool bool22 = ba.readBool();
		bool bool33 = ba.readBool();
		int int81 = ba.readInt8();
		cout << str1 << endl;
		cout << int321 << endl;
		cout << int161 << endl;
		cout << double11 << endl;
		cout << bool11 << endl;
		cout << bool22 << endl;
		cout << bool33 << endl;
		cout << int81 << endl;
		int socketID = lws_get_socket_fd(wsi);
		send(socketID, wb);
		_receivedData.insert(_receivedData.end(), inData, inData + len);
	}
	

	size_t remainingSize = lws_remaining_packet_payload(wsi);
	int isFinalFragment = lws_is_final_fragment(wsi);
	if (remainingSize == 0 && isFinalFragment)
	{
		std::vector<char>* frameData = new (std::nothrow) std::vector<char>(std::move(_receivedData));

		// reset capacity of received data buffer
		_receivedData.reserve(WS_RESERVE_RECEIVE_BUFFER_SIZE);
		ssize_t frameSize = frameData->size();

		bool isBinary = (lws_frame_is_binary(wsi) != 0);

		if (!isBinary)
		{
			frameData->push_back('\0');
		}
		delete frameData;
	}
}
void WebServer::onDisconnect(int socketID)
{
}
void WebServer::onError(int socketID, const string& message)
{
}
