#pragma once

#include"../src/BaseWindow.h"
#include"../src/Globals.h";
#include"SignUP.h"


class SignUP;

class SignIN : public BaseWindow
{

private:

	//char username[32];
	//char password[32];
	static char username[32];
	static char password[32];
	SignUP* signUpWindow{};

public:

	void getSignUpWindow(SignUP* signUp) {

		signUpWindow = signUp;
	}

	SignIN(SignUP* signUp);

	

	void RemoveBackgroundStyle();

	void RenderUsernameInput(char* username);
	void RenderPasswordInput(char* password);
	void RenderLaunch();
	void RenderIconButton();

	void Render() override;

};

