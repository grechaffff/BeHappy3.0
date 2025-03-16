#include "ErrorWindow.h"

void ErrorWindow::Render()
{

    if (!IsOpen) {
        return;
        exit(1);
    }

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(400 , 150));
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("authServer", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
  
    ImGui::SetCursorPos(ImVec2(200, 170));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::Text("x");

    MessageError(ErrorMessage);
    ImGui::SetCursorPos(ImVec2(75, 120));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // ������� ������ ��� ������ 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // ������� ������ ��� ��� ��������� �� ������ 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // ������� ������ ��� ��� ������� �� ������ 


    ImGui::SetCursorPos(ImVec2(360, 5));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
    if (ImGui::Button("x", ImVec2(0, 0))) {      
        IsOpen = false;
        exit(IsOpen);
    }

    ImGui::PopStyleColor(6);
    ImGui::PopStyleVar();
    ImGui::End();

}

ErrorWindow::ErrorWindow() : BaseWindow("authServer", { 0 , 0 }, { 0, 0 })
{
   

}


ErrorWindow& ErrorWindow::Instance()
{
    static ErrorWindow errorWin;
    return errorWin;
}

void ErrorWindow::MessageError(std::string& message)
{
    ImGui::SetCursorPos(ImVec2(100, 60));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 0.20f, 0.50f, 2.50f));
    ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(message.c_str()).x) / 2);
    ImGui::Text(message.c_str());
   // std::cout << "MessageError:" << message << std::endl;

    ImGui::PopStyleColor();
}

std::string ErrorWindow::ErrorMessage;
