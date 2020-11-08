#define _CRT_SECURE_NO_WARNINGS

#include "WebServer.h"
#include <string>
#include <sstream>
#include <iostream>

int main()
{
	WebServer webServer("0.0.0.0", 8080, "client-webpage");
	if (webServer.init() != 0)
	{
		system("pause");
		return 0;
	}

	webServer.run();
	
	system("pause");
	return 0;
}
