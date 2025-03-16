#include "ErrorManager.h"

void ErrorManager::ErrorConnectServer(std::string& errorMessage)
{

   
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::SetNextWindowSize(ImVec2(400, 150));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.06f, 0.07f, 1.00));

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("ServerError", &ServerError, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::SetCursorPos(ImVec2(200, 170));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::Text("x");

    ImGui::SetCursorPos(ImVec2(90, 60));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::Text(u8"Сервер не отвечает");
    ImGui::SetCursorPos(ImVec2(75, 120));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 


    ImGui::SetCursorPos(ImVec2(10, 10));
   

    ImGui::SetCursorPos(ImVec2(360, 5));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
    if (ImGui::Button("x", ImVec2(0, 0))) {
        ServerError = false;
        exit(WM_QUIT);

    }
    ImGui::SetCursorPos(ImVec2(30, 15));


    ImGui::PopStyleColor(8);
    

    ImGui::PopStyleVar();
    ImGui::End();
}
