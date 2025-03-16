#pragma once
#include"../src/Globals.h"

class ErrorManager
{

private:

	bool ServerError;

public:

	bool getServerError() { return ServerError; }
	void ErrorConnectServer(std::string& errorMessage);
};