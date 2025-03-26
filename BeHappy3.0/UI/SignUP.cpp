#include"SignUP.h"
#include"../resources/Icons/InitIcon.h"
#include "../src/WindowManager.h"
#include"../UI/ErrorWindow.h"
SignUP::SignUP(SignIN* signIn)
    : BaseWindow("SignUP", { 400, 450 }, { 0, 0 }), signInWindow(signIn) {
    IsOpen = false;

}



void SignUP::RemoveBackgroundStyle()
{

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 

}

void SignUP::RenderUsernameInput(char* username)
{

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.03f, 0.04f, 0.05f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.20f, 1.20f, 0.0f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    //ImGuiInputTextFlags_Password что бы пароль отображался ****

    ImGui::SetNextItemWidth(250);

    ImGui::SetCursorPos(ImVec2(70, 150));


    ImGui::InputText("###", username, 32);

    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    ImU32 borderColor = IM_COL32(255, 105, 180, 255);


    float thickness = 1.0f;

    // Рисуем рамку
    draw_list->AddRect(p_min, p_max, borderColor, 0.0f, 0, thickness);

}

void SignUP::RenderEmailInput(char* email)
{
    ImGui::SetNextItemWidth(250);
    ImGui::SetCursorPos(ImVec2(70, 230));
   

    ImGui::PushID("Email");
    ImGui::InputText("##", email, 32);
   

    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    ImU32 borderColor = IM_COL32(255, 105, 180, 255);


    float thickness = 1.0f;

    // Рисуем рамку
    draw_list->AddRect(p_min, p_max, borderColor, 0.0f, 0, thickness);

    ImGui::PopID();
}

void SignUP::RenderPasswordInput(char* password)
{

    ImGui::SetCursorPos(ImVec2(70, 300));
    ImGui::SetNextItemWidth(250);
    ImGui::InputText("##", password, 32, ImGuiInputTextFlags_Password);

    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    ImU32 borderColor = IM_COL32(255, 105, 180, 255);


    float thickness = 1.0f;

    // Рисуем рамку
    draw_list->AddRect(p_min, p_max, borderColor, 0.0f, 0, thickness);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));

}

void SignUP::RenderLaunch()
{

    ImGui::SetCursorPos(ImVec2(130, 385));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7.0f);


    if (ImGui::Button("Launch", ImVec2(140, 35))) {

        if (strlen(password) == 0 && strlen(username) == 0 && strlen(email) == 0) {
            WindowManager::Instance().CloseWindow("SignUP");
            std::cout << "username and password empty:" << std::endl;
            std::string data = "username and password empty:";
            ErrorWindow::Instance().ErrorMessage = data;
            WindowManager::Instance().CloseWindow("SignUP");
            WindowManager::Instance().OpenWindow("authServer");
            ImGui::PopStyleVar();
            return;
        }

        std::string action = "Register";
        std::string message = action + "|" + username + "|" + email + "|" + password;

        boost::asio::write(socket_ssl, boost::asio::buffer(message));
       

        char response[1024];
        size_t len = socket_ssl.read_some(boost::asio::buffer(response));
        std::string res(response, len);
        std::cout << "Server response: " << std::string(response, len) << std::endl;


      

        res.erase(0, res.find_first_not_of(" \t\n\r"));
        res.erase(res.find_last_not_of(" \t\n\r") + 1);

        if (res == "User not uniq") {
            std::cout << "User not uniq:" << std::endl;
            WindowManager::Instance().CloseWindow("SignUP");
            ErrorWindow::Instance().ErrorMessage = res;
            WindowManager::Instance().OpenWindow("authServer");
        }
        else if (res == "Registration succesfull") {
            WindowManager::Instance().CloseWindow("SignUP");
            std::cout << "Successful:" << std::endl;
            WindowManager::Instance().OpenWindow("ShopMenu");
        }
    }
    ImGui::PopStyleVar();
}

void SignUP::RenderIconButton()
{

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.00f, 0.20f, 0.50f, 0.00f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    ImGui::SetCursorPos(ImVec2(200, 350));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button(ICON_NEW_USER)) {

       


    }
    ImGui::SetCursorPos(ImVec2(150, 350));
    if (ImGui::Button(ICON_USER)) {

        IsOpen = false;
        signInWindow->IsOpen = true;

    }
   

}




void SignUP::Render()
{
    if (!IsOpen) {
        return;
        exit(1);
    }
   
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("SignUP", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPos(ImVec2(10, 15));
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

    ImGui::PushFont(font2);
    ImGui::SetCursorPos(ImVec2(140, 70));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::Text("SIGN UP");
    ImGui::SetCursorPos(ImVec2(75, 120));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::Text("Username");

    ImGui::PopStyleColor(2);

    RemoveBackgroundStyle();

    ImGui::SetCursorPos(ImVec2(360, 5));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
    if (ImGui::Button("x", ImVec2(0, 0))) {

        IsOpen = false;
        exit(IsOpen);

    }
    ImGui::PopStyleColor(4);

    ImGui::SetCursorPos(ImVec2(75, 200));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::Text("Email");
    ImGui::PopStyleColor();



    ImGui::SetCursorPos(ImVec2(75, 270));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::Text("Password");
    ImGui::PopStyleColor();

   




    RenderUsernameInput(username);
    RenderEmailInput(email);

    RenderPasswordInput(password);

    RenderLaunch();
    RenderIconButton();

    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    ImGui::PopStyleVar(2);
    ImGui::PopFont();
    ImGui::PopStyleColor(10);
    ImGui::End();

   
}

char SignUP::username[32] = { 0 };
char SignUP::email[32] = { 0 };
char SignUP::password[32] = { 0 };