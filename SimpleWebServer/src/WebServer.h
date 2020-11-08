#pragma once

#pragma once
#include "TCPServer.h"
#include <string>

class WebServer : public TCPServer
{
private:
	std::string _indexDir;
public:
	WebServer(const char* ipAddress, int port, std::string indexDir); 

protected:

	// Handler for client connections
	virtual void onClientConnected(SOCKET clientSocket);

	// Handler for client disconnections
	virtual void onClientDisconnected(SOCKET clientSocket);

	// Handler for when a message is received from the client
	virtual void onMessageReceived(SOCKET clientSocket, const std::string& message);
};