

#include"SignIN.h"

#include"SignUP.h"
#include"../resources/Icons/InitIcon.h"
#include"../src/TextureManager.h"
#include"../src/App.h"
#include"../src/ErrorManager.h"
#include"../UI/ErrorWindow.h"
#include"../UI/UsersInfo.h"
#include"../UI/CreateShop.h"

SignIN::SignIN(SignUP* signUp)
    : BaseWindow("SignIN", { 400, 450 }, { 0, 0 }), signUpWindow(signUp) {
   

}


void SignIN::RemoveBackgroundStyle() {

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 

}


void SignIN::RenderUsernameInput(char* username) {
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.03f, 0.04f, 0.05f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.20f, 1.20f, 0.0f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    //ImGuiInputTextFlags_Password что бы пароль отображался ****

    ImGui::SetNextItemWidth(250);

    ImGui::SetCursorPos(ImVec2(70, 150));


    ImGui::InputText("###", username, 32);
   

    // Получаем координаты InputText
    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Цвет и толщина обводки
    ImU32 borderColor = IM_COL32(255, 105, 180, 255);

    //ImU32 borderColor = IM_COL32(255, 105, 180, 255);
    float thickness = 1.0f;

    // Рисуем рамку
    draw_list->AddRect(p_min, p_max, borderColor, 0.0f, 0, thickness);


}

void SignIN::RenderPasswordInput(char* password) {

    ImGui::SetCursorPos(ImVec2(70, 230));
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

void SignIN::RenderLaunch() {

    ImGui::SetCursorPos(ImVec2(130, 385));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 7.0f);


    if (ImGui::Button("Launch", ImVec2(140, 35))) {

        if (strlen(password) == 0 && strlen(username) == 0) {
            std::string data = "username and password empty:";
            std::cout << "username and password empty:" << std::endl;
            WindowManager::Instance().CloseWindow("SignIN");
            ErrorWindow::Instance().ErrorMessage = data;
            WindowManager::Instance().OpenWindow("authServer");
            ImGui::PopStyleVar();
            return;
        }

        std::string action = "Login";

        std::string email = "";  // Пустое поле для email
        std::string message = action + "|" + username + "|" + email + "|" + password;
        
        std::cout << username << std::endl;
        std::cout << password << std::endl;


       
        
        boost::asio::write(socket_ssl, boost::asio::buffer(message));


        char response[1024];
        size_t len = socket_ssl.read_some(boost::asio::buffer(response));
        std::string res(response, len);
        std::cout << "Server response: " << res << std::endl;

        // Разделяем строку по '|'
        std::string server_response;
        std::string user_role;
        std::string id;
        size_t delimiter = res.find('|');
       
        if (delimiter != std::string::npos) {
            size_t second_delimiter = res.find('|' ,  delimiter + 1);
            
            if (second_delimiter != std::string::npos) {
                server_response = res.substr(0, delimiter);  // До первого '|'
                user_role = res.substr(delimiter + 1, second_delimiter - delimiter - 1);  // Между двумя '|'
                id = res.substr(second_delimiter + 1);  // После второго '|'

                std::cout << "Server Response: " << server_response << std::endl;
                std::cout << "User Role: " << user_role << std::endl;
                std::cout << "UserID:" << id << std::endl;
            }
        }
        else {
            server_response = res;
        }

        // Убираем лишние пробелы и символы новой строки
        size_t first = server_response.find_first_not_of(" \t\n\r");
        if (first != std::string::npos) {
            server_response.erase(0, first);
        }

        size_t last = server_response.find_last_not_of(" \t\n\r");
        if (last != std::string::npos) {
            server_response.erase(last + 1);
        }

        // Сохраняем пользователя
        UserInfo::Instance().user = username;
        CreateShop::Instance().role = user_role;
        CreateShop::Instance().userID = stoi(id);
        

        // Проверяем ответ сервера
        if (server_response == "username and password empty") {
            WindowManager::Instance().CloseWindow("SignIN");
            std::cout << "Error: Username and password cannot be empty." << std::endl;
            WindowManager::Instance().OpenWindow("authServer");
        }
        else if (server_response == "User not found") {
            WindowManager::Instance().CloseWindow("SignIN");
            std::cout << "Error: User not found." << std::endl;
            ErrorWindow::Instance().ErrorMessage = server_response;
            WindowManager::Instance().OpenWindow("authServer");
        }
        else if (server_response == "incorrect password") {
            std::cout << "Error: Incorrect password." << std::endl;
            WindowManager::Instance().CloseWindow("SignIN");
            ErrorWindow::Instance().ErrorMessage = server_response;
            WindowManager::Instance().OpenWindow("authServer");
        }
        else if (server_response == "Login Successfull") {
            WindowManager::Instance().CloseWindow("SignIN");
            std::cout << "Login Successful." << std::endl;
            ErrorWindow::authentication = true;
            WindowManager::Instance().OpenWindow("ShopMenu");
        }
        else {
            std::cout << "Unknown response: [" << server_response << "]" << std::endl;
        }
        

    }
    ImGui::PopStyleVar();
}

void SignIN::RenderIconButton() {
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.00f, 0.20f, 0.50f, 0.00f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    ImGui::SetCursorPos(ImVec2(200, 275));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);


    //ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);


    if (ImGui::Button(ICON_NEW_USER)) {


        

        IsOpen = false;
        signUpWindow->IsOpen = true;

    }
    ImGui::SetCursorPos(ImVec2(150, 275));
    if (ImGui::Button(ICON_USER)) {




    }

   

}

void SignIN::Render()
{

    if (!IsOpen) {
        return;
    }
    SDL_SetWindowSize(window, 400, 450);
    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("SignIN", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    if (ImGui::IsAnyItemHovered()) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }
    else {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }

    ImGui::SetCursorPos(ImVec2(10, 15));

   

    ImGui::Image((ImTextureID)(intptr_t)(TextureManager::Instance().getShopImage()
        ? TextureManager::Instance().getShopImage()
        : TextureManager::Instance().GetPlaceholderTexture()),
        ImVec2(70, 70));
    

    ImGui::SetCursorPos(ImVec2(140, 70));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::Text("SIGN IN");

    ImGui::SetCursorPos(ImVec2(75, 120));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::Text("Username");
    RemoveBackgroundStyle(); // no Style Button

    ImGui::SetCursorPos(ImVec2(360, 5));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
    if (ImGui::Button("x", ImVec2(0, 0))) {
        IsOpen = false;
        SDL_Quit(); // Работает для выхода  , но консоль остается . 
        exit(IsOpen);
       
     
    }

    ImGui::SetCursorPos(ImVec2(75, 200));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::Text("Password");

    ImGui::PopStyleColor(7);

    //static char username[32];
    //static char password[32];

    RenderUsernameInput(username);
    RenderPasswordInput(password);
    RenderLaunch();
    RenderIconButton();

   std::this_thread::sleep_for(std::chrono::milliseconds(5));
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(10);
    ImGui::End();
}

char SignIN::username[32] = { 0 };  
char SignIN::password[32] = { 0 };