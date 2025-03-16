#include"../UI/CreateShop.h"
#include"../src/WindowManager.h"
#include"../src/TextureManager.h"

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
   
    ImGui::Image((ImTextureID)(intptr_t)(TextureManager::Instance().getShopImage()
        ? TextureManager::Instance().getShopImage()
        : TextureManager::Instance().GetPlaceholderTexture()),
        ImVec2(70, 70));

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
    if (ImGui::InputText("", search, sizeof(search)) && !is_typing) {
        is_typing = true;  // Устанавливаем флаг, что пользователь вводит текст
        search[0] = '\0';
    }
    

    if (!is_typing && strcmp(search, "") == 0) {
        is_typing = false;
    }

  
    ImGui::SetCursorPos(ImVec2(130, 385));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));   
    ImGui::SetCursorPos(ImVec2(130, 350));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопк
    static std::string filename;

   
    ImGui::SetCursorPos(ImVec2(80, 180));
    
   
    ImGui::Text(u8"Add Logo");
    ImGui::PushID("LogoButton"); // для того что бы не было конфликта имен
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::SetCursorPos(ImVec2(200, 180));
    if (ImGui::Button(FOLDER)) {
        filename = OpenFileDialog();
        if (filename.empty()) {
            std::cerr << "No file selected." << std::endl;
            //return -1;
        }
    }
    ImGui::PopID();
    
    
    

    ImGui::PopStyleColor(6);


    ImGui::SetCursorPos(ImVec2(80, 230));

    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::Text(u8"Add Banner");   
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));   
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::SetCursorPos(ImVec2(220, 230));
    ImGui::PushID("BannerButton");
    if (ImGui::Button(FOLDER)) {
        filename = OpenFileDialog();
        if (filename.empty()) {
            std::cerr << "No file selected." << std::endl;
            //return -1;
        }
    }
    ImGui::PopID();
    
    ImGui::PopStyleColor(3);

    ImGui::SetCursorPos(ImVec2(135, 350));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7.0f);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(85.0f / 255.0f, 47.0f / 255.0f, 117.0f / 255.0f, 1.0f));
    

   
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

        if (ImGui::Button(u8"Отправить на проверку", ImVec2(300, 35))) {



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
