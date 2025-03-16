#include "UsersInfo.h"
#include"CreateShop.h"
#include"../src/WindowManager.h"
#include"../UI/CreateShop.h"
UserInfo& UserInfo::Instance()
{
    static UserInfo userInfo;
    return userInfo;
}

UserInfo::UserInfo() : BaseWindow("UserInfo", { 0 , 0 }, { 0, 0 })
{


}

void UserInfo::Render()
{
   
        ImGui::SetNextWindowPos(ImVec2(10, 150));
        ImGui::SetNextWindowSize(ImVec2(780, 440));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1, 1, 1, 0.50f));

        ImGui::Begin("UserInfo", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
       
        
        MouseClicked();

        ImGui::SetWindowFocus();

        myProfile();
        UsersInfo();
        //CreateShop();
       
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(5);
        ImGui::End();

    
}

void UserInfo::MouseClicked()
{
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        ImVec2 mousePos = ImGui::GetMousePos();

        if (!ImGui::IsMouseHoveringRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax()) &&
            !ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)))
        {
            IsOpen = false;
        }
    }

}

void UserInfo::myProfile()
{

    ImGui::SetCursorPos(ImVec2(10, 90));
    ImGui::Separator();


    ImGui::SetCursorPos(ImVec2(30, 110));
    ImGui::Text(u8"Мой профиль: ");


    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.40f, 0.696f, 1.30f));
    ImGui::SetCursorPos(ImVec2(200, 110));
    if (user[0] == '\0') {  // Проверяем, является ли строка пустой
        ImGui::SetCursorPos(ImVec2(200, 110));

        ImGui::Text(u8"Войдите в аккаунт!");

    }
    else {
        ImGui::Text("%s", user);  // Выводим ник пользователя
    }


    ImGui::PopStyleColor();

}

void UserInfo::UsersInfo()
{
  
    ImGui::SetCursorPos(ImVec2(60, 180));
    ImGui::Text(u8"Город: ");



    ImGui::SetCursorPos(ImVec2(60, 230));
    ImGui::Text(u8"Количество сделок: ");


    if (CreateShop::role == "admin") {

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
        ImGui::SetCursorPos(ImVec2(470, 110));
        if (ImGui::Button(u8"Управление магазином")) {

            WindowManager::Instance().CloseWindow("ShopMenu");
            WindowManager::Instance().CloseWindow("UserInfo");
            WindowManager::Instance().OpenWindow("ShopManager");
        }
        
        ImGui::PopStyleColor(3);
    }
    else if (CreateShop::role == "user") {

    }
    // CreateShop
    
    CreateShop();

    ImGui::SetCursorPos(ImVec2(40, 50));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button("User profile")) {

       
    }

    ImGui::SetCursorPos(ImVec2(200, 50));
    if (ImGui::Button("My finances")) {

      

    }

    ImGui::SetCursorPos(ImVec2(630, 50));
    if (ImGui::Button("Alerts")) {


    }


    ImGui::SetCursorPos(ImVec2(480, 50));
    if (ImGui::Button("My orders")) {

    }

    ImGui::SetCursorPos(ImVec2(370, 50));
    if (ImGui::Button("Settings")) {


        
    }


    ImGui::SetCursorPos(ImVec2(10, 10));
    if (ImGui::Button(LEFT)) {

        IsOpen = false;
        
    }

   
}

void UserInfo::CreateShop()
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    ImGui::SetCursorPos(ImVec2(60, 280));
    if (ImGui::Button(u8"Создание магазина")) {
       
        WindowManager::Instance().CloseWindow("ShopMenu");
        WindowManager::Instance().CloseWindow("UserInfo");
        WindowManager::Instance().OpenWindow("CreateShop");
    }

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();


}

std::string UserInfo::user;
