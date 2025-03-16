#pragma once



#include"Globals.h"
#include"../UI/SignIN.h"
#include"WindowManager.h"
#include"../UI/Shop.h"

enum class AppState;


class App {


private:

    void HandleWindowMovement(SDL_Window* window, SDL_Event* event);

    SDL_Window* window;
    SDL_GLContext gl_context;
    ImVec4 clear_color;
    bool running;
    bool moving;
    int mouseOffsetX, mouseOffsetY;



public:

	App();
	~App();

    bool ConnectToServer(std::string& errorMessage);
	void Run();


};