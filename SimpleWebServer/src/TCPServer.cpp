#include "TCPServer.h"
#include <iostream>
#include <string>
#include <sstream>

TCPServer::TCPServer(const char* ipAddress, int port)
	: _ipAddress(ipAddress), _port(port)
{
}

int TCPServer::init()
{
	//Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cout << "Can't initialize winsock data!!!" << std::endl;
		return wsOk;
	}

	//Create a socket
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket == INVALID_SOCKET)
	{
		std::cout << "Can't initialize socket!!!" << std::endl;
		return WSAGetLastError();
	}

	//Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(_port);
	inet_pton(AF_INET, _ipAddress, &hint.sin_addr);

	if (bind(_socket, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{		
		std::cout << "Can't bind port and IP address!!!" << std::endl;
		return WSAGetLastError();
	}

	//Tell Winsock the socket is for listening 
	if (listen(_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cout << "Can't listen on socket!!!" << std::endl;
		return WSAGetLastError();
	}

	//Create the master file descriptor set and zero it
	FD_ZERO(&_master);

	//Add our first socket that we're interested in interacting with; the listening socket!
	FD_SET(_socket, &_master);

	return 0;
}

int TCPServer::run()
{
	//This will be changed by the \quit command (see below, bonus not in video!)
	bool running = true;

	while (running)
	{
		fd_set copy = _master;

		//See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		//Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			//Makes things easy for us doing this assignment
			SOCKET sock = copy.fd_array[i];

			//Is it an inbound communication?
			if (sock == _socket)
			{
				//Accept a new connection
				SOCKET client = accept(_socket, nullptr, nullptr);

				//Add the new connection to the list of connected clients
				FD_SET(client, &_master);

				onClientConnected(client);
			}
			else //It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				//Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					//Drop the client
					onClientDisconnected(sock);
					closesocket(sock);
					FD_CLR(sock, &_master);
				}
				else
				{
					onMessageReceived(sock, std::string(buf));
				}
			}
		}
	}

	//Remove the listening socket from the master file descriptor set and close it to prevent anyone else trying to connect.
	FD_CLR(_socket, &_master);
	closesocket(_socket);

	while (_master.fd_count > 0)
	{
		//Get the socket number
		SOCKET sock = _master.fd_array[0];

		//Remove it from the master file list and close the socket
		FD_CLR(sock, &_master);
		closesocket(sock);
	}

	//Cleanup winsock
	WSACleanup();
	return 0;
}


void TCPServer::sendToClient(SOCKET clientSocket, const std::string& message)
{
	send(clientSocket, message.c_str(), message.length() + 1, 0);
}

void TCPServer::onClientConnected(SOCKET clientSocket)
{
}

void TCPServer::onClientDisconnected(SOCKET clientSocket)
{
}

void TCPServer::onMessageReceived(SOCKET clientSocket, const std::string& msg)
{
}
