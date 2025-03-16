#pragma once
#include"../src/BaseWindow.h"

class ErrorWindow : public BaseWindow
{

public:


	void Render() override;

	ErrorWindow();
	static std::string  ErrorMessage;
	static ErrorWindow& Instance();
	void MessageError(std::string& message);

private:
	
	

};