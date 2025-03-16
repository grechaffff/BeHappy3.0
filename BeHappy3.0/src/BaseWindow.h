#pragma once

#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include"Globals.h"

//#include"SignUP.h"

class BaseWindow {

protected:
	std::string title;
	ImVec2 size;
	ImVec2 position;


public:
	bool IsOpen;
	

	BaseWindow(const std::string& title, ImVec2 size, ImVec2 position)
		: title(title), size(size), position(position), IsOpen(true) {
	}


	const std::string& GetTitle() const {
		return title;
	}

	virtual void Render() = 0; // Чисто виртуальный метод для отрисовки окна

	virtual ~BaseWindow() = default;
};


#endif // BASEWINDOW_H