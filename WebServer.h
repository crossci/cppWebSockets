#ifndef _WEBSERVER_H
#define _WEBSERVER_H

#include "WebSocketServer.h"

class WebServer :public WebSocketServer
{
public:
	WebServer(int port) :WebSocketServer(port)
	{

	}
	virtual void onConnect(int socketID);
	virtual void onMessage(struct lws *wsi, void* in, int len);
	virtual void onDisconnect(int socketID) ;
	virtual void   onError(int socketID, const string& message);
};
#endif