#pragma once
#include<vector>
#include<memory>
#include"BaseWindow.h"
#include"../UI/SignUP.h"

class BaseWindow;

class WindowManager {

private:
   // std::vector<std::shared_ptr<BaseWindow>> windows;

    std::unordered_map<std::string, std::shared_ptr<BaseWindow>> windows;

public:

    void AddWindow(const std::string& name, std::shared_ptr<BaseWindow> window);

    void RenderAll();

    static WindowManager& Instance();

    template <typename T>
    bool HasWindow() const;
        
    
    std::shared_ptr<BaseWindow> FindWindow_SDL3(const std::string& title);
       
    void AdjustWindowSize(SDL_Window* window);

    void OpenWindow(const std::string& title);
       
    void CloseWindow(const std::string& title);
       
};

template<typename T>
inline bool WindowManager::HasWindow() const
{
    for (const auto& [title, window] : windows) {
        if (std::dynamic_pointer_cast<T>(window)) {
            return true;
        }
    }
    return false;

}
