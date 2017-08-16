
#include "WebServer.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	WebServer server(9090);
	server.run();
	system("pause");
}