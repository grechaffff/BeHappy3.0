#pragma once
#include"../src/BaseWindow.h"

class CreateShop : public  BaseWindow
{


public:

	CreateShop();


	void Render() override;
	void EnterNameShop();
	std::string OpenFileDialog();
	static std::string role;
	static int userID;

	static CreateShop& Instance();

private:
	std::vector<std::string> images;

	static std::string input;
	static char search[128];
	bool is_typing = false;
	
};