﻿#include"../UI/CreateShop.h"
#include"../src/WindowManager.h"
#include"../src/TextureManager.h"
#include"nfd.h"
#include"../UI/AsyncImageClient.h"
#include"../UI/ErrorWindow.h"

CreateShop::CreateShop() : BaseWindow("CreateShop", { 0 , 0 }, { 0, 0 })
{


}


void CreateShop::Render()
{
    if (!IsOpen) {
        return;
    }
    
    ImGui::SetNextWindowPos(ImVec2(0 , 0));
    ImGui::SetNextWindowSize(ImVec2(600 , 450));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.06f, 0.07f, 1.00));
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("CreateShop", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
   
    bool IsClicked = false;
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 0.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 

    if (ImGui::ImageButton("##", (ImTextureID)(intptr_t)(TextureManager::Instance().getShopImage()
        ? TextureManager::Instance().getShopImage()
        : TextureManager::Instance().GetPlaceholderTexture()),
        ImVec2(70, 70)))
    {
        IsClicked = true;
    }

    if (IsClicked) {

        WindowManager::Instance().CloseWindow("CreateShop");
        WindowManager::Instance().OpenWindow("ShopMenu");


    }
    ImGui::PopStyleColor(4);

    if (ImGui::IsAnyItemHovered()) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }
    else {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }

    EnterNameShop();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    ImGui::End();
}

std::string CreateShop::OpenFileDialog()
{
    return std::string();
}

CreateShop& CreateShop::Instance()
{
    static CreateShop create;
    return create;
}

void CreateShop::EnterNameShop()
{
    if (!is_typing && strcmp(search, "") == 0) {
        ImGui::SetCursorPos(ImVec2(80, 120));
        ImGui::Text(input.c_str());
    }
    else {
        is_typing = false;
    }
    ImGui::SetCursorPos(ImVec2(80, 120));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.05f, 0.06f, 0.07f, 0.70f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.20f, 1.20f, 0.0f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    ImGui::SetNextItemWidth(380);

   
    // Обработка ввода текста
    if (ImGui::InputText("###", search, 32)) {
        is_typing = true;  // Устанавливаем флаг, что пользователь вводит текст
        //search[0] = '\0';
    }
    

    if (!is_typing && strcmp(search, "") == 0) {
        is_typing = false;
    }
    
  

    ImGui::SetCursorPos(ImVec2(130, 385));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));   
    ImGui::SetCursorPos(ImVec2(130, 350));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопк
    
   
    ImGui::SetCursorPos(ImVec2(80, 180));
    
    boost::asio::io_context io_context;
   
    

    static bool buttonDisabledLogo = false;

    ImGui::Text(u8"Add Logo");
    ImGui::PushID("LogoButton"); // для того что бы не было конфликта имен
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::SetCursorPos(ImVec2(200, 180));
    if (!buttonDisabledLogo && ImGui::Button(FOLDER)) {
        nfdchar_t* outpath = nullptr;
       nfdresult_t result = NFD_OpenDialog("png,jpg", nullptr, &outpath);
       if (result == NFD_OKAY) {
           images.emplace_back(outpath);
           free(outpath);
           std::cout << "Файл выбран N1" << std::endl;
           buttonDisabledLogo = true;
       }
       else if (result == NFD_CANCEL) {
           std::string data = u8"Логотип не выбран";
           std::cout << "Файл не выбран N1" << std::endl;
           ErrorWindow::Instance().ErrorMessage = data;
           WindowManager::Instance().CloseWindow("CreateShop");
           WindowManager::Instance().OpenWindow("authServer");

           free(outpath);
       }
      

    }
    ImGui::PopID();
    
    if (buttonDisabledLogo) {
        ImGui::BeginDisabled();
        ImGui::Button(FOLDER);
        ImGui::EndDisabled();
    }
    

    ImGui::PopStyleColor(6);



    ImGui::SetCursorPos(ImVec2(80, 230));

    static bool buttonDisabledBanner = false;

    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::Text(u8"Add Banner");   
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));   
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::SetCursorPos(ImVec2(220, 230));
    ImGui::PushID("BannerButton");
    if (!buttonDisabledBanner && ImGui::Button(FOLDER)) {
        nfdchar_t* outpath2 = nullptr;
        nfdresult_t result2 = NFD_OpenDialog("png,jpg", nullptr, &outpath2);
        if (result2 == NFD_OKAY) {
            images.emplace_back(outpath2);
            free(outpath2);
            std::cout << "Файл выбран N2" << std::endl;
            buttonDisabledBanner = true;
        }
        else if (result2 == NFD_CANCEL) {
            std::string data = u8"Баннер не выбран";
            std::cout << "Файл не выбран N1" << std::endl;
            ErrorWindow::Instance().ErrorMessage = data;
            WindowManager::Instance().CloseWindow("CreateShop");
            WindowManager::Instance().OpenWindow("authServer");
            free(outpath2);
        }
       
    }
    if (buttonDisabledBanner) {
        ImGui::BeginDisabled();
        ImGui::Button(FOLDER);
        ImGui::EndDisabled();
    }
    
    
   
    
   
  


   // std::vector<std::string> images = { outpath ? outpath : "", outpath2 ? outpath2 : "" };

   



    ImGui::PopID();
    
    ImGui::PopStyleColor(3);

    ImGui::SetCursorPos(ImVec2(135, 350));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(85.0f / 255.0f, 47.0f / 255.0f, 117.0f / 255.0f, 1.0f));
    
    
    static bool buttonSendShop = false;
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    if (strcmp(role.c_str(), "user") == 0) {
        if (ImGui::Button(u8"Отправить на проверку", ImVec2(300, 35))) {



        }
        ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Темный фон
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));    //
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
          
           
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"Доступно только администраторам").x) / 2);
            ImGui::SetTooltip(u8"Доступно только администраторам");
            

            
        }
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar();
    }
    


    else if (strcmp(role.c_str(), "admin") == 0) {

        if (!buttonSendShop && ImGui::Button(u8"Отправить на проверку", ImVec2(300, 35))) {

            std::cout << "Отправляем изображения, количество: " << images.size() << std::endl;
            for (const auto& img : images) {
                std::cout << "Путь: " << img << std::endl;
            }
            if (images.size() == 0 || images.size() == 1) {

                std::cout << "Добавьте изображение магазина:" << std::endl;
                std::string data = u8"Добавьте изображение магазина:";
                WindowManager::Instance().CloseWindow("CreateShop");
                WindowManager::Instance().CloseWindow("ShopMenu");
                ErrorWindow::Instance().ErrorMessage = data;
                WindowManager::Instance().OpenWindow("authServer");
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);
                return;

            }
            if (strcmp(search, "") == 0) {
                std::cout << u8"Enter store name:" << std::endl;
                std::string data = u8"Введите название магазина:";
                WindowManager::Instance().CloseWindow("CreateShop");
                WindowManager::Instance().CloseWindow("ShopMenu");
                ErrorWindow::Instance().ErrorMessage = data;
                WindowManager::Instance().OpenWindow("authServer");
            }
            else {
                auto client = std::make_shared<AsyncImageClient>(io_context, "127.0.0.1", 7272, userID , search, images );

                client->Start("127.0.0.1", 7272 , userID); // Вызываем старт уже после создания shared_ptr
                buttonSendShop = true;

                io_context.run();


            }
           
          

        }
        if (buttonSendShop) {
            ImGui::BeginDisabled();

            ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10.0f);
            ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Темный фон
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.5f, 0.0f, 1.0f));    //
                     
          
            ImGui::Button(u8"Отправить на проверку");
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {

               
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(u8"Ваш магазин в обработке").x) / 2);
                ImGui::SetTooltip(u8"Ваш магазин в обработке");



            }
            ImGui::EndDisabled();
            ImGui::PopStyleColor(2);
            ImGui::PopStyleVar();
            
        }

    }
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();

    ImGui::SetCursorPos(ImVec2(200, 20));
    ImGui::Text(u8"Создание магазина");


    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 


    ImGui::SetCursorPos(ImVec2(565, 5));
    if (ImGui::Button("x")) {

        WindowManager::Instance().CloseWindow("CreateShop");
        WindowManager::Instance().OpenWindow("ShopMenu");

    }
    ImGui::PopStyleColor(3);

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.05f, 0.06f, 0.07f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.20f, 1.20f, 0.0f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
 

    ImGui::PopStyleColor(3);
}



std::string CreateShop::input = "Enter a name";
char CreateShop::search[128] = "";
std::string CreateShop::role;
int CreateShop::userID;