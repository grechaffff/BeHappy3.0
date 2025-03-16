#include"WindowManager.h"
#include"BaseWindow.h"
#include"../UI/Shop.h"
void WindowManager::AddWindow(const std::string& name, std::shared_ptr<BaseWindow> window) {

    windows[window->GetTitle()] = window;

    
}



void WindowManager::RenderAll() {

    for (auto& [title, window] : windows) {
        if (window->IsOpen) {
            window->Render();
        }
       
    }
    
}

WindowManager& WindowManager::Instance()
{
    static WindowManager instance;
    return instance;
}



std::shared_ptr<BaseWindow> WindowManager::FindWindow_SDL3(const std::string& title)
{
    auto it = windows.find(title);
    return (it != windows.end()) ? it->second : nullptr;

    
    return nullptr; // ���� ���� �� �������
}
void WindowManager::AdjustWindowSize(SDL_Window* window) {
    static int prevWidth = -1, prevHeight = -1; // ����������� ���������� ��� �������� ���������� ��������
    int currentWidth, currentHeight;
    SDL_GetWindowSize(window, &currentWidth, &currentHeight);

    int targetWidth = currentWidth;
    int targetHeight = currentHeight;

    // ��������� �������� ����
    auto shopWindow = FindWindow_SDL3("ShopMenu");
    if (shopWindow && shopWindow->IsOpen) {
        targetWidth = 800;
        targetHeight = 600;
    }
    else {
        auto signInWindow = FindWindow_SDL3("SignIN");
        if (signInWindow && signInWindow->IsOpen) {
            targetWidth = 400;
            targetHeight = 450;
        }
        else {
            auto signUpWindow = FindWindow_SDL3("SignUP");
            if (signUpWindow && signUpWindow->IsOpen) {
                targetWidth = 400;
                targetHeight = 450;
            }
            else {
                auto userInfoWindow = FindWindow_SDL3("UserInfo");
                if (userInfoWindow && userInfoWindow->IsOpen) {
                    targetWidth = 500;
                    targetHeight = 400;
                }
            }
        }
        
        auto ErrorWindow = FindWindow_SDL3("authServer");
        if (ErrorWindow && ErrorWindow->IsOpen) {
            targetWidth = 400;
            targetHeight = 150;
        }
        else {
            auto createShopName = FindWindow_SDL3("CreateShop");
            if (createShopName && createShopName->IsOpen) {
                targetWidth = 600;
                targetHeight = 450;
            }
            else {
                auto StoreManagm = FindWindow_SDL3("ShopManager");
                if (StoreManagm && StoreManagm->IsOpen) {
                    targetWidth = 800;
                    targetHeight = 600;
                }
            }
        }
    }

    // ���������, ���������� �� ������� �� ��������� � �����������
    if (currentWidth != targetWidth || currentHeight != targetHeight) {
        SDL_SetWindowSize(window, targetWidth, targetHeight);
        glViewport(0, 0, targetWidth, targetHeight);
        ImGui::GetIO().DisplaySize = ImVec2((float)targetWidth, (float)targetHeight);
        prevWidth = targetWidth;
        prevHeight = targetHeight;
        // std::cout << "������ ���� ������ �� " << targetWidth << "x" << targetHeight << std::endl;
    }
}
    

void WindowManager::OpenWindow(const std::string& title)
{

    auto window = FindWindow_SDL3(title);
    if (window) {
       // SDL_SetWindowSize(window , 800 , 600);
        window->IsOpen = true;
    }
    else {
        std::cout << "Find Window not found: " << std::endl;
    }
}

void WindowManager::CloseWindow(const std::string& title)
{

    auto window = FindWindow_SDL3(title);
    if (window) {
        window->IsOpen = false;
    }
    else {

        std::cout << "Window not found:" << std::endl;
    }
}

