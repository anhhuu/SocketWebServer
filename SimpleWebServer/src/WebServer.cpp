#include <string>
#include <sstream>
#include <iostream>

#include "httpHeader.h"
#include "httpRequest.h"
#include "httpResponse.h"
#include "httpUtils.h"
#include "FileProcessor.h"
#include "httpResponseContent.h"

#include "WebServer.h"

void WebServer::onMessageReceived(SOCKET clientSocket, const std::string& message)
{
	std::cout << "Received message..." << std::endl;
	HTTP::Request req(message);
	//std::cout << message;
	HTTP::Extensions extens;
	HTTP::ResponseContent content;
	HTTP::ResponseCode resCode = HTTP::ResponseCode::OK;
	std::vector<HTTP::Header> headers;
	
	if (req.getMethod() == HTTP::Method::POST)
	{
		if (req.getData()[0].getValue("username") == "admin" && req.getData()[0].getValue("pass") == "admin")
		{
			resCode = HTTP::ResponseCode::MOVED_PERMANENTLY;
			HTTP::Header location = HTTP::Header("Location", "info.html");
			
			headers.push_back(location);
		}
		else
		{
			resCode = HTTP::ResponseCode::NOT_FOUND;
		}
	}
	else if(req.getMethod() == HTTP::Method::GET || req.getMethod() == HTTP::Method::HEAD)
	{
		std::string path = req.getURL(_indexDir);
		std::string contentStr;
		if (path == _indexDir + "/")
		{
			extens = HTTP::Extensions::HTML;
			contentStr = FileProcessor::readText(path + "index.html");
			content.setContent(contentStr);
		}
		else
		{
			std::string extendStr = path.substr(path.find_last_of(".") + 1, path.length() - 1);
			extens = HTTP::Utils::extendFromString(extendStr);
			if (extens == HTTP::Extensions::CSS || extens == HTTP::Extensions::JS || extens == HTTP::Extensions::HTML)
			{
				contentStr = FileProcessor::readText(path);
				content.setContent(contentStr);
			}
			else
			{
				contentStr = FileProcessor::readBinary(path);
				content.setContent(contentStr);
			}
		}
		if (contentStr == "")
		{
			resCode = HTTP::ResponseCode::NOT_FOUND;
		}
		content.setExtens(extens);
	}
	else
	{
		resCode = HTTP::ResponseCode::INTERNAL_SERVER_ERROR;
	}

	if (resCode == HTTP::ResponseCode::NOT_FOUND)
	{
		std::string contentStr = FileProcessor::readText(_indexDir + "/404.html");
		content.setContent(contentStr);
	}

	HTTP::Header cacheControl = HTTP::Header("Cache-Control", "no-cache, private");
	HTTP::Header contentType = HTTP::Header("Content-Type", content.getContentType());
	HTTP::Header contentLength = HTTP::Header("Content-Length", std::to_string(content.getContent().size()));

	headers.push_back(cacheControl);
	headers.push_back(contentType);
	headers.push_back(contentLength);

	HTTP::Response res(resCode, req.getVersion(), headers, content);

	std::string output = res.toResponseMessageStr();

	sendToClient(clientSocket, output);

	std::cout << "Sent message..." << std::endl;
	//std::cout << output;
}

WebServer::WebServer(const char* ipAddress, int port, std::string indexDir)
	: TCPServer(ipAddress, port), _indexDir(indexDir)
{
}

void WebServer::onClientConnected(SOCKET clientSocket)
{
	std::cout << "Client Connected..." << std::endl;
}

void WebServer::onClientDisconnected(SOCKET clientSocket)
{
	std::cout << "Client Disconnected..." << std::endl;
}
