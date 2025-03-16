#pragma once
#include"../src/BaseWindow.h"
#include"../src/Globals.h"


class UserInfo : public BaseWindow
{

private:

	bool UsersInf = false;

	
public:


	static UserInfo &Instance();
	
	static std::string user;
	

	UserInfo();

	void Render() override;

	void MouseClicked();

	void myProfile();

	void UsersInfo();

	void CreateShop();
};