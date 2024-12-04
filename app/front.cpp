#include "front.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

namespace MyApp {

    ImTextureID LoadImage(const string& filePath) {
        int width, height, channels;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

        if (data) {
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            GLenum format;
            if (channels == 3) {
                format = GL_RGB; // Use GL_RGB if the image has 3 channels
            }
            else if (channels == 4) {
                format = GL_RGBA; // Use GL_RGBA if the image has 4 channels
            }
            else {
                cerr << "Unsupported image format with " << channels << " channels" << endl;
                return 0; // Handle unsupported formats
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
            return static_cast<ImTextureID>(texture);  // Cast to ImTextureID
        }

        cerr << "nullptr" << endl;  // If loading failed
    }

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
        ImGui::Text("%s", "skdasdsa.txt");
        ImGui::Image(LoadImage("./imagem.png"), ImVec2(100, 100));
        static float value = 0.5f;
        ImGui::DragFloat("Value", &value);
        float ado = 0;
       
        
        ImGui::InputFloat("coloque algum numero", &ado);
        ImGui::End();


        //ImGui::ShowDemoWindow();
    }
}
