#pragma once

#ifndef SIGNUP_H
#define SIGNUP_H


#include "../src/BaseWindow.h"  // Исправленный путь
#include "../src/Globals.h"
#include"SignIN.h"

class SignIN;


class SignUP : public  BaseWindow
{

private:

	
	static char username[32];
	static char email[32];
	static char password[32];
	SignIN* signInWindow{};

public:


	

	SignUP(SignIN* signIn);

	void RemoveBackgroundStyle();

	void RenderUsernameInput(char* username);
	void RenderEmailInput(char* email);
	void RenderPasswordInput(char* password);
	void RenderLaunch();
	void RenderIconButton();


	void Render() override;



};


#endif // SIGNUP_H