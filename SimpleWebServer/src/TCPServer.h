#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

class TCPServer
{

public:
	TCPServer(const char* ipAddress, int port);

	//Initialize the listener
	int init();

	//Run the listener
	int run();

protected:

	//Handler for client connections
	virtual void onClientConnected(SOCKET clientSocket);

	//Handler for client disconnections
	virtual void onClientDisconnected(SOCKET clientSocket);

	//Handler for when a message is received from the client
	virtual void onMessageReceived(SOCKET clientSocket, const std::string& message);

	//Send a message to a client
	void sendToClient(SOCKET clientSocket, const std::string& message);

private:
	const char*	_ipAddress;	//IP Address server will run on
	int	_port; //Port for the Web service
	SOCKET _socket; //Internal FD for the listening socket
	fd_set	_master; //Master file descriptor set
};
