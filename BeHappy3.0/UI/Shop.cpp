#include"Shop.h"
#include<iostream>


bool is_typing = false;






Shop::Shop(WindowManager& manager)
    : BaseWindow("ShopMenu", { 400, 300 }, { 100, 100 }), manager(manager) {
}




void Shop::Render() {

    


    if (!IsOpen) return;
    //SDL_SetWindowSize(window, 800, 600);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.05f, 0.06f, 0.07f, 1.00));
    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.00f, 0.50f, 0.670f, 0.50f));
    

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
    ImGui::Begin("ShopMenu", &IsOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    ImGui::PushFont(font2);

    if (ImGui::IsAnyItemHovered()) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }
    else {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }

    ImGui::Image((ImTextureID)(intptr_t)(TextureManager::Instance().getShopImage()
        ? TextureManager::Instance().getShopImage()
        : TextureManager::Instance().GetPlaceholderTexture()),
        ImVec2(70, 70));

    float imageSize = 160.0f;
    float padding = 70.0f;

    float totalWidth = ImGui::GetContentRegionAvail().x;

    // Вычисляем, сколько изображений поместится в строку
    int imagesPerRow = static_cast<int>((totalWidth + padding) / (imageSize + padding));
    if (imagesPerRow < 1) imagesPerRow = 1;

    // Вычисляем ширину строки из изображений + отступов между ними
    float rowWidth = imagesPerRow * imageSize + (imagesPerRow - 1) * padding;

    // Центрируем строку по горизонтали (оставляем одинаковый отступ слева и справа)
    float leftOffset = (totalWidth - rowWidth) * 0.5f;
    if (leftOffset < 0.0f) leftOffset = 0.0f; // На всякий случай

    // Отступ сверху, если нужно (можно убрать SetCursorPos если не нужен вертикальный отступ)
    ImGui::SetCursorPosY(160.0f);

    for (size_t i = 0; i < imageMemoryList.size(); ++i) {
        // Переход на новую строку и установка отступа слева
        if (i % imagesPerRow == 0) {
            if (i != 0)
                ImGui::NewLine();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + leftOffset);
        }

        ImGui::Image(imageMemoryList[i], ImVec2(imageSize, imageSize));

        if ((i + 1) % imagesPerRow != 0)
            ImGui::SameLine(0.0f, padding);
    }


    

    RemoveBackground();
    ImGui::SetCursorPos(ImVec2(760, 5));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 0.70f));
    if (ImGui::Button("x", ImVec2(0, 0))) {
       
        exit(IsOpen);
        SDL_Quit();
       
    }

    RemoveBackground();
    InputStyle();
    CreateInput();
    CreateSearch();
    Create_Category();
    CreateUser_Credits();



    ClearImGui();
   
}


void Shop::CreateSearch()
{
    ImGui::SetCursorPos(ImVec2(535, 25));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    if (ImGui::Button("search")) {

    }
    ImGui::PopStyleColor(3);

    ImGui::SetCursorPos(ImVec2(240, 100));
    RemoveBackground();

    if (ImGui::Button("The Shop")) {



    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(4);

}


void Shop::RemoveBackground()
{
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.10f, 1.20f, 1.00f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f)); // убирает задний фон при нажатии на кнопку 


}

void Shop::CreateInput()
{
    static const char* input = "Search...";
    static  char search[128];

    //ImGui::PushFont(font3);

    if (!is_typing && strcmp(search, "") == 0) {
        ImGui::Text(input);
    }
    else {
        is_typing = false;
    }
    ImGui::SetCursorPos(ImVec2(150, 25));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.05f, 0.06f, 0.07f, 0.70f));
    ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.20f, 1.20f, 0.0f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
    ImGui::SetNextItemWidth(380);

    if (ImGui::InputText("", search, sizeof(search)) && !is_typing) {
        is_typing = true;
        search[0] = '\0';
    }

    ImVec2 p_min = ImGui::GetItemRectMin();
    ImVec2 p_max = ImGui::GetItemRectMax();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();


    ImU32 borderColor = IM_COL32(255, 0, 255, 255);


    float thickness = 1.0f;

    // Рисуем рамку
    draw_list->AddRect(p_min, p_max, borderColor, 0.0f, 0, thickness);


    if (!is_typing && strcmp(search, "") == 0) {
        is_typing = false;
    }

}

void Shop::InputStyle()
{
    ImGui::SetCursorPos(ImVec2(90, 20));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 2));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1, 1, 1, 0.30f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 1, 1, 0.30f));




    ImGui::SetCursorPos(ImVec2(155, 27));

}

void Shop::Create_Category()
{


    static bool List = false;
    ImGui::SetCursorPos(ImVec2(10, 90));
    ImGui::Separator();
    ImGui::SetCursorPos(ImVec2(115, 100));
    ImGui::Text("Category");
    ImGui::SetCursorPos(ImVec2(80, 100));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));




    if (ImGui::Button(CATEGORY)) {
        List = !List;

    }
    if (List) {

        const char* item1[] = { "Goods","VPN","Hip-hop","Blok","SSH","Programming" };
        int transfer = 0;
        ImGui::SetNextItemWidth(200);
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.05f, 0.06f, 0.07f, 0.55f));
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.05f, 0.06f, 0.07f, 0.95f));
        ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.05f, 0.06f, 0.07f, 0.95f));   // устанавливаем цвет фона для выделенного текста0.05f, 0.06f, 0.07f, 0.95f
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.05f, 0.06f, 0.07f, 0.95f)); // устанавливаем цвет при нажатии в ListBox
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(1, 1, 1, 0.50f));
        int  height_in_items = 15;
        if (ImGui::ListBox("##", &transfer, item1, IM_ARRAYSIZE(item1), height_in_items)) {

            if (transfer == 0) {
                // ... реализация ...
            }

            if (transfer == 1) {


            }





            // Создание категорий 
        }

        ImGui::PopStyleColor(5);

    }

    ImGui::PopStyleColor(3);

}

void Shop::CreateUser_Credits()
{

    ImGui::SetCursorPos(ImVec2(650, 60));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // убирает задний фон кнопки 
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.00f, 0.50f, 0.670f, 0.50f)); // убирает задний фон при наведении на кнопку 
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.00f, 0.0f, 0.0f, 0.00f));


    if (ImGui::Button(USERS)) {


        //Users = !Users;

        if (&manager != nullptr) {
            manager.OpenWindow("UserInfo");

        }
        else {

            std::cout << "Nullptr" << std::endl;
        }

    }

    ImGui::SetCursorPos(ImVec2(705, 57));
    ImGui::Text("|");
    ImGui::SetCursorPos(ImVec2(730, 60));
    if (ImGui::Button(CREDITS)) {

    }

    ImGui::PopStyleColor(3);

}

void Shop::ClearImGui()
{
    ImGui::PopStyleColor(17);

    ImGui::PopFont();
    ImGui::PopStyleVar(2);
    ImGui::End();

}
