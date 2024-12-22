#include "front.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "storage.h"
#include "mainFrame.h"

using namespace std;
using namespace storage;
bool stateUpload = true;
bool deleteOriginFiles = false;

namespace MyApp {
    char input[400] = "";
    string inputResult;
    vector<GLuint> textureDelete;
    ImTextureID LoadImage(const string fileName) {
        const string& filePath = "../images/" + fileName;
        int width, height, channels;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
        GLuint texture;

        if (data) {
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
            return  static_cast<ImTextureID>(texture);  // Cast to ImTextureID
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

    static void makeFiles() {
        ImVec2 childSize = ImVec2(150.0f, 200.0f);

        ImGui::BeginChild("mainFrame", ImVec2(0, 0), true);
        static vector<returnObject> files;
        files = getAllFiles();
        int accumulator = 0;
        for (const auto& object : files) {
            ImVec2 availableSpace = ImGui::GetContentRegionAvail();
            ImGui::PushID(accumulator);
            ImGui::BeginChild("objectFrame", childSize);
            GLuint texture = LoadImage(object.nameImage);
            ImGui::Image(texture, ImVec2(childSize.x, childSize.x));
            ImGui::Text("%s", object.nameFile.c_str());
            ImGui::Spacing();
            ImGui::EndChild();
            if (ImGui::GetCursorPosX() + childSize.x > availableSpace.x) {
                ImGui::NewLine();  
            }
            else {
                ImGui::SameLine();
            }
            textureDelete.push_back(texture);
            accumulator++;
            ImGui::PopID();
        }
        ImGui::EndChild();
        
    }

    void makeWindowInput() {
        if (!stateUpload) {
            bool* p_open = NULL;
            ImGuiWindowFlags window_flags = 0;
            ImGuiIO& io = ImGui::GetIO();
            ImVec2 displaySize = io.DisplaySize;
            float windowWidth = 700.0f;
            float windowHeight = 200.0f;
            float windowX = (displaySize.x - windowWidth) / 2.0f;
            float windowY = (displaySize.y - windowHeight) / 2.0f;
            ImGui::SetNextWindowPos(ImVec2(windowX, windowY), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
            window_flags |= ImGuiWindowFlags_NoTitleBar;
            window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
            window_flags |= ImGuiWindowFlags_NoMove;
            ImGui::Begin("uploadBlock", p_open, window_flags);
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("X").x - 15.00f);
            if (ImGui::Button("X")) stateUpload = true;
            ImGui::Text("%s", "SELECT THE FILE PATH TO COMPACT:");
            ImGui::Spacing();
            ImGui::PushItemWidth(600);
            ImGui::InputText(" ", input, sizeof(input));
            ImGui::PopItemWidth;
            ImGui::SameLine();
            if (ImGui::Button("OPEN")) {
                inputResult = string(input);
                MainFrame::compactRegister(inputResult, deleteOriginFiles); // review this shit, return isn't working
                stateUpload = true;
            }
            ImGui::NewLine;
            ImGui::Spacing();
            ImGui::Checkbox("Delete Origin Files?", &deleteOriginFiles);
            ImGui::End();
        }
    }

    void menuBar()
    {
       if (ImGui::BeginMainMenuBar())
       {
           ImGui::Button("Settings");
           ImGui::Button("Filter");
           if (stateUpload) {
               if (ImGui::Button("Upload")) stateUpload = false;
           }
           ImGui::EndMainMenuBar();
       }
       makeWindowInput();
    }

    void adjustFont() {
        ImGuiIO& io = ImGui::GetIO();
        io.FontGlobalScale = 1.25f;
    }

    void freeTexture() {
        for (const auto& textures : textureDelete) {
            glDeleteTextures(1, &textures);
        }
    }

    void RenderUi()
    {   
        adjustFont();
        makepWindow();
        menuBar();
        makeFiles();
        ImGui::End();
       //ImGui::ShowDemoWindow();
    }
}
