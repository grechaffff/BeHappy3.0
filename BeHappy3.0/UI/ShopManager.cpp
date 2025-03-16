#include"ShopManager.h"
#include"../src/WindowManager.h"
ShopManager::ShopManager() : BaseWindow {"ShopManager" , { 0 , 0}  , { 0 ,0 }}
{

}



void ShopManager::Render()
{

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.06f, 0.07f, 1.00));
    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.00f, 0.50f, 0.670f, 0.50f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));

   
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("ShopManager", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::SetCursorPos(ImVec2(720, 515));
    
    if (ImGui::IsAnyItemHovered()) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }
    else {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }

    bool IsClicked = false;
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 0.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 
   
    if (ImGui::ImageButton("", (ImTextureID)(intptr_t)(TextureManager::Instance().getShopImage()
        ? TextureManager::Instance().getShopImage()
        : TextureManager::Instance().GetPlaceholderTexture()),
        ImVec2(70, 70)))
    {
        IsClicked = true;
    }

    if (IsClicked) {
       
            WindowManager::Instance().CloseWindow("ShopManager");
            WindowManager::Instance().OpenWindow("ShopMenu");

        
    }
    ImGui::PopStyleColor(4);
    


    ImGui::SetCursorPos(ImVec2(10, 320));
    ImGui::Separator();

    AddBanner();
    GoodsManag();
    Settings();
    Community();
    StatisticsInfo();
    OtherInfo();
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar();
    ImGui::End();
}

void ShopManager::AddBanner()
{

    
    std::string message = u8"Обновить баннер";
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(message.c_str()).x) / 2);
    ImGui::SetCursorPos(ImVec2(10, 40));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Прозрачный фон кнопки
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.6f, 0.2f, 1.0f, 1.0f)); // Белая граница

    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f); // Толщина границы
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f); // Закругление углов

    if (ImGui::Button(u8"Обновить баннер", ImVec2(780, 130))) {
        // Действие при нажатии
    }

    ImGui::SetCursorPos(ImVec2(260, 95));
    
    ImGui::SetCursorPos(ImVec2(10, 3));
    UpdateLogo();

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(5);
    ExitWindow();

}

void ShopManager::ExitWindow()
{
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 
    ImGui::SetCursorPos(ImVec2(760, 3));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
    if (ImGui::Button("x", ImVec2(0, 0))) {

       

    }

    ImGui::PopStyleColor(5);
}

void ShopManager::UpdateLogo()
{


    std::string message = u8"Обновить лого";
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(message.c_str()).x) / 2);
    ImGui::SetCursorPos(ImVec2(50, 130));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Прозрачный фон кнопки
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.6f, 0.2f, 1.0f, 1.0f)); // Белая граница

    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.5f); // Толщина границы
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f); // Закругление углов
    ImGui::SetWindowFontScale(0.6f); // Уменьшает текст в 2 раза
    if (ImGui::Button(message.c_str(), ImVec2(120, 120))) {
        // Действие при нажатии
    }
    ImGui::SetWindowFontScale(1.0f);

    ImGui::PopStyleColor(5);
    ImGui::PopStyleVar(2);
}

void ShopManager::GoodsManag()
{
    
    ImGui::SetCursorPos(ImVec2(60, 280));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button(u8"Управление товарами")) {

    }

    
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
}

void ShopManager::Settings()
{
    
    ImGui::SetCursorPos(ImVec2(350, 280));
   

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button("Settings")) {

    }

    
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
}

void ShopManager::Community()
{
   
    ImGui::SetCursorPos(ImVec2(470, 280));


    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button("Community")) {

    }

   
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();

}

void ShopManager::StatisticsInfo()
{
    
    ImGui::SetCursorPos(ImVec2(630, 280));


    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button("Statistics")) {

    }

    
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
}

void ShopManager::OtherInfo()
{
    ImGui::SetCursorPos(ImVec2(60, 360));
    ImGui::Text(u8"Дата основания:");

    ImGui::SetCursorPos(ImVec2(60, 420));
    ImGui::Text(u8"Род деятельности:");


    ImGui::SetCursorPos(ImVec2(60, 480));
    ImGui::Text(u8"График работы: 9:00 - 18:00");
}
