#include "front.h"
#include "imgui.h"
#include "stdio.h"

namespace MyApp {

    ImGuiWindowFlags makepWindow()
    {
        bool* p_open = NULL;
        ImGuiWindowFlags window_flags = 0;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        window_flags |= ImGuiWindowFlags_NoTitleBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
        window_flags |= ImGuiWindowFlags_NoMove;
        ImGui::Begin("Settings", p_open, window_flags);
        return window_flags;
        //test
    }

    void menuBar()
    {
       if (ImGui::BeginMainMenuBar())
       {
           ImGui::Button("Settings");
           ImGui::Button("Filter");

           ImGui::EndMainMenuBar();
       }
    }

    void adjustFont() {
        ImGuiIO& io = ImGui::GetIO();
        io.FontGlobalScale = 1.25f;
    }

    void RenderUi()
    {
        MyApp::adjustFont();
        MyApp::makepWindow();
        MyApp::menuBar();
        ImGui::Button("PRESS MEEEEE");
        
        static float value = 0.5f;
        ImGui::DragFloat("Value", &value);
        float ado = 0;
       
        
        ImGui::InputFloat("coloque algum numero", &ado);
        ImGui::End();


        //ImGui::ShowDemoWindow();
    }
}
