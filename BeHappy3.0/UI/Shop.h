#pragma once

#include"../src/BaseWindow.h"
#include"../src/Globals.h"
#include"../UI/UsersInfo.h"
#include"../src/WindowManager.h"


class Shop : public BaseWindow
{

private:

	WindowManager& manager;

public:

	
	Shop() = delete;
	Shop(WindowManager & manager);

	void Render() override;

	void CreateSearch();
	void RemoveBackground();
	void CreateInput();
	void InputStyle();
	void Create_Category();
	void CreateUser_Credits();
	void ClearImGui();

};
