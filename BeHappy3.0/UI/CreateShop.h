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

	static CreateShop& Instance();

private:


	static std::string input;
	static char search[128];
	bool is_typing = false;
};