#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <mutex>
#include "DrawThread.h"
#include "GuiMain.h"
#include "imgui.h"
#define IM_PI 3.14159265359f

std::string url_encode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (unsigned char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        }
        else {
            escaped << '%' << std::setw(2) << int(c);
        }
    }
    return escaped.str();
}
void ApplyModernTheme() {
    ImGuiStyle& style = ImGui::GetStyle();

    // General UI Colors
    // Change window background to a darker shade
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.14f, 1.0f);  // Dark background for the entire UI blocks

    // Border color for windows and panels
    style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.35f, 1.0f);

    // Frame (input fields, buttons) background color
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.22f, 1.0f);  // Darker background for input fields
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.3f, 1.0f);  // Lighter on hover
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.3f, 0.3f, 0.35f, 1.0f);  // Darker when active


    // Buttons
    style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.47f, 0.75f, 1.0f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.6f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.37f, 0.65f, 1.0f);

    // Text
    style.Colors[ImGuiCol_Text] = ImVec4(0.85f, 0.9f, 0.95f, 1.0f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.5f, 0.5f, 0.55f, 1.0f);

    // Headers
    style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.45f, 0.65f, 1.0f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.35f, 0.55f, 0.75f, 1.0f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2f, 0.4f, 0.6f, 1.0f);

    // Spacing & Rounding
    style.WindowRounding = 10.0f;
    style.FrameRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.ItemSpacing = ImVec2(10, 8);
    style.ScrollbarSize = 14.0f;
    style.FramePadding = ImVec2(10, 6);
    style.WindowPadding = ImVec2(14, 14);
    //ImGui::GetIO().FontGlobalScale = 1.5f;  // Increase text size

}
void ApplyModernTheme1() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Set general colors
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.10f, 0.15f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.18f, 0.18f, 0.18f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.28f, 0.28f, 0.28f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.38f, 0.38f, 0.38f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.45f, 0.75f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.35f, 0.65f, 0.95f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.35f, 0.55f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.45f, 0.45f, 0.45f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.85f, 0.85f, 1.0f));

    // Set spacing and padding
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(10, 8);
    style.WindowRounding = 8.0f;
    style.FrameRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 8.0f;

}

void DrawAppWindow(void* common_ptr) {
    ApplyModernTheme();

    auto common = static_cast<CommonObjects*>(common_ptr);
    ImGui::SetNextWindowSize(ImVec2(800, 800), ImGuiCond_FirstUseEver);
    ImGui::Begin("Book Manager", nullptr, ImGuiWindowFlags_NoResize);

    // Modern Styling
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.12f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 0.7f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.6f, 0.9f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.3f, 0.6f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8, 8));

    ImGui::TextColored(ImVec4(0.3f, 0.7f, 1.0f, 1.0f), "Select Input Type:");

    static char input_buffer[100] = "";
    static int input_mode = 0;
    static int limit = 0;
    static char sort_option[50] = "";
    static char fields_option[100] = "";
    static char kind_option[50] = "";
    static bool bot_filter = false;
    static int offset = 0;
    static char date_buffer[20] = "";

    const char* input_labels[] = { "Search", "Work ID", "Author ID", "ISBN", "Recent Changes" };
    ImGui::Columns(5, nullptr, false);
    for (int i = 0; i < 5; i++) {
        ImGui::PushID(i);
        if (ImGui::RadioButton(input_labels[i], input_mode == i)) {
            input_mode = i;
        }
        ImGui::PopID();
        ImGui::NextColumn();
    }
    ImGui::Columns(1);
    ImGui::NewLine();

    ImGui::BeginChild("InputSection", ImVec2(0, 150), true, ImGuiWindowFlags_AlwaysUseWindowPadding);
    const char* label = (input_mode == 0) ? "Search Query" :
        (input_mode == 1) ? "Work ID" :
        (input_mode == 2) ? "Author ID" :
        (input_mode == 3) ? "ISBN" : nullptr;
    if (label != nullptr) {
        std::string input_label = std::string(label) + "##input";
        ImGui::InputText(input_label.c_str(), input_buffer, sizeof(input_buffer));
    }
    if (input_mode == 0) {
        ImGui::SliderInt("Limit Results##limit", &limit, 1, 100);
        ImGui::InputText("Sort By##sort", sort_option, sizeof(sort_option));
        ImGui::InputText("Fields##fields", fields_option, sizeof(fields_option));
    }
    if (input_mode == 4) {
        ImGui::SliderInt("Limit Results##limit", &limit, 1, 100);
        ImGui::InputText("Kind##kind", kind_option, sizeof(kind_option));
        //ImGui::SliderInt("Offset##offset", &offset, 0, 10000);
        ImGui::InputText("Date##date", date_buffer, sizeof(date_buffer));
        ImGui::Checkbox("Filter by Bots", &bot_filter);

    }
    ImGui::EndChild();

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
    if (ImGui::Button("Submit##submit", ImVec2(120, 35))) {

        if (strlen(input_buffer) > 0 || input_mode == 4) {
            std::lock_guard<std::mutex> lock(common->data_mutex);
            common->error_message.clear(); 

            std::string base_url, query_param;
            switch (input_mode) {
            case 0:
                base_url = "https://openlibrary.org/search.json";
                query_param = "?q=" + url_encode(std::string(input_buffer));
                if (limit > 0) query_param += "&limit=" + std::to_string(limit);
                if (strlen(sort_option) > 0) query_param += "&sort=" + url_encode(std::string(sort_option));
                if (strlen(fields_option) > 0) query_param += "&fields=" + url_encode(std::string(fields_option));
                break;
            case 1:
                base_url = "https://openlibrary.org/works/";
                query_param = url_encode(std::string(input_buffer)) + ".json";
                break;
            case 2:
                base_url = "https://openlibrary.org/authors/";
                query_param = url_encode(std::string(input_buffer)) + ".json";
                break;
            case 3:
                base_url = "https://openlibrary.org/books/";
                query_param = url_encode(std::string(input_buffer)) + ".json";
                break;
            case 4:
                base_url = "https://openlibrary.org/recentchanges";
                if (strlen(date_buffer) == 0) { query_param = ".json?limit=" + std::to_string(limit) ; }
                if (strlen(kind_option) > 0) query_param += "&kind=" + url_encode(std::string(kind_option));
                if (bot_filter) query_param += "&bot=true";
                //if (offset > 0) query_param += "&offset=" + std::to_string(offset);
                if (strlen(date_buffer) > 0) {
                    query_param += "/" + std::string(date_buffer) + ".json";
                }
                break;
            }

            common->url = base_url + query_param;
            common->query_type = (input_mode == 0) ? "search" :
                (input_mode == 1) ? "work" :
                (input_mode == 2) ? "author" :
                (input_mode == 3) ? "book" : "recent_changes";

            std::cout << "[DEBUG] Generated API Request URL: " << common->url << std::endl;
            common->start_download = true;
            common->cv.notify_all();
        }
    }
    ImGui::PopStyleVar();

    ImGui::PopStyleColor(5);
    ImGui::PopStyleVar(2);
    if (common->start_download && !common->json_ready) {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.3f));  // Transparent black background

        if (ImGui::Begin("Loading", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
            ImVec2 window_pos = ImGui::GetWindowPos();
            ImVec2 window_size = ImGui::GetWindowSize();
            ImVec2 center = ImVec2(window_pos.x + window_size.x * 0.5f, window_pos.y + window_size.y * 0.5f);

            ImGui::SetCursorPos(ImVec2(window_size.x * 0.5f - 10, window_size.y * 0.5f - 10));
            /*ImGui::Text("Loading...");*/

            static float rotation = 0.0f;
            rotation += ImGui::GetIO().DeltaTime * 5.0f;
            if (rotation > IM_PI * 2.0f) rotation -= IM_PI * 2.0f;

            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            const int num_segments = 15;
            const float radius = 15.0f;
            const float angle_step = IM_PI * 2.0f / num_segments;
            for (int i = 0; i < num_segments; i++) {
                float angle = rotation + angle_step * i;
                float alpha = (float)i / num_segments;
                ImVec2 circle_pos = ImVec2(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
                draw_list->AddCircleFilled(circle_pos, 3.0f, IM_COL32(255, 255, 255, (int)(alpha * 255)));
            }
            ImGui::End();
        }

        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }
    if (!common->error_message.empty()) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.3f, 0.0f, 0.0f, 1.0f));  // Dark red background
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 0.2f, 0.2f, 1.0f));  // Bright red border
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.6f, 0.6f, 1.0f));  // Light red text

        ImGui::BeginChild("ErrorAlert", ImVec2(0, 50), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        ImGui::TextWrapped("[!] Error: %s", common->error_message.c_str());
        ImGui::EndChild();

        ImGui::PopStyleColor(3);  
    }
    if (common->json_ready && common->error_message.empty()) {
        ApplyModernTheme1();
        ApplyModernTheme();
        ImGui::BeginChild("Results", ImVec2(800, 450), true, ImGuiWindowFlags_AlwaysUseWindowPadding);

        ImGui::TextColored(ImVec4(0.9f, 0.7f, 0.4f, 1.0f), "Search Results:");
        ImGui::Separator();

        if (common->query_type == "search") {
            for (size_t i = 0; i < common->search_results.size(); i++) {
                ImGui::PushID(static_cast<int>(i));
                ImGui::PushTextWrapPos(0.0f);  

                ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f), "Title: %s", common->search_results[i].title.c_str());
                ImGui::TextWrapped("Author: %s", common->search_results[i].author.c_str());

                ImGui::PopTextWrapPos(); 
                ImGui::Separator();
                ImGui::PopID();
            }
        }
        else if (common->query_type == "work" || common->query_type == "book") {
            for (size_t i = 0; i < common->books.size(); i++) {
                ImGui::PushID(static_cast<int>(i));
                ImGui::TextColored(ImVec4(0.7f, 0.9f, 0.7f, 1.0f), "Book Details:");
                ImGui::Text("Title: %s", common->books[i].title.c_str());
                ImGui::Text("Author: %s", common->books[i].author.c_str());
                ImGui::Text("Publish Date: %s", common->books[i].publish_date.c_str());
                ImGui::Text("Cover ID: %s", common->books[i].cover_id.c_str());
                ImGui::TextWrapped("Description: %s", common->books[i].description.c_str());
                ImGui::Separator();
                ImGui::PopID();
            }
        }
        else if (common->query_type == "author") {
            ImGui::TextColored(ImVec4(0.9f, 0.8f, 0.6f, 1.0f), "Author Information:");
            ImGui::Text("Name: %s", common->author_details.name.c_str());
            ImGui::Text("ID: %s", common->author_details.author_id.c_str());
            ImGui::Text("Birth Date: %s", common->author_details.birth_date.c_str());
            ImGui::Text("Death Date: %s", common->author_details.death_date.c_str());
            ImGui::Text("Top Work: %s", common->author_details.top_work.c_str());
            ImGui::Text("Works Count: %d", common->author_details.work_count);
            ImGui::TextWrapped("Bio: %s", common->author_details.biography.empty() ? "Not available" : common->author_details.biography.c_str());
        }
        else if (common->query_type == "recent_changes") {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.3f, 1.0f), "Recent Changes:");
            for (size_t i = 0; i < common->recent_changes.size(); i++) {
                ImGui::PushID(static_cast<int>(i));
                ImGui::Text("Change ID: %s", common->recent_changes[i].id.c_str());
                ImGui::Text("Type: %s", common->recent_changes[i].kind.c_str());
                ImGui::Text("Author: %s", common->recent_changes[i].author.c_str());
                ImGui::Text("IP: %s", common->recent_changes[i].ip.c_str());
                ImGui::Text("Timestamp: %s", common->recent_changes[i].timestamp.c_str());
                ImGui::TextWrapped("Comment: %s", common->recent_changes[i].comment.c_str());
                ImGui::Separator();
                ImGui::PopID();
            }
        }

        ImGui::EndChild();
        ImGui::PopStyleColor(10);  // Restore original colors
    }
    ImGui::End();
}
void DrawThread::operator()(CommonObjects& common) {
    GuiMain(DrawAppWindow, &common);
    common.exit_flag = true;
}
