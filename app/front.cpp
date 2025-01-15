#include "front.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "storage.h"
#include "mainFrame.h"

using namespace std;
using namespace storage;
bool stateUpload = true;
bool stateDescompact = true;
bool deleteOriginFiles = false;

namespace MyApp {
    char input[400] = "";
    char outputPath[400] = "";
    string inputResult;
    string outputPathResult;
    vector<GLuint> textureDelete;
    vector<string> checkedFiles;
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
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (!stateUpload || !stateDescompact) {
            window_flags |= ImGuiWindowFlags_NoInputs;
        }
        ImGui::Begin("Main", p_open, window_flags);
        return window_flags;
    }

    static void checkboxFiles(string fileName) {
        bool checkedFile = false;
        bool checkFileAlreadyInVector = false;
        for (const auto& fileSelected : checkedFiles) {
            if (fileName == fileSelected) {
                checkedFile = true;
                checkFileAlreadyInVector = true;
            }
        }
        ImGui::Checkbox(("##" + fileName).c_str(), &checkedFile); //the ## it's for not show any text after the checkbox
        if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        if (checkedFile && !checkFileAlreadyInVector) checkedFiles.push_back(fileName);
        else if (!checkedFile) {
            auto fileToRemove = find(checkedFiles.begin(), checkedFiles.end(), fileName);
            if (fileToRemove != checkedFiles.end()) checkedFiles.erase(fileToRemove);
        };
    }

    static void makeFiles() {
        ImGuiIO& io = ImGui::GetIO();
        ImVec2 childSize = ImVec2(100.0f, 200.0f);
        static vector<returnObject> files;
        ImGui::BeginChild("mainFrame", ImVec2(0, 0), true);
        files = getAllFiles();
        int accumulator = 0;
        for (const auto& object : files) {
            ImVec2 availableSpace = ImGui::GetContentRegionAvail();
            ImGui::PushID(accumulator);
            ImGui::BeginChild("objectFrame", childSize);
            checkboxFiles(object.nameFile);
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
            float windowPositionX = ImGui::GetWindowPos().x;
            float windowPositionY = ImGui::GetWindowPos().y;
            float windowX = ((displaySize.x - windowWidth) / 2.0f) + windowPositionX;
            float windowY = (((displaySize.y - windowHeight) / 2.0f) + windowPositionY) * 0.90f;
            window_flags |= ImGuiWindowFlags_NoTitleBar;
            window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
            ImGui::SetNextWindowPos(ImVec2(windowX, windowY), ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
            ImGui::SetNextWindowFocus();
            ImGui::Begin("uploadBlock", p_open, window_flags);
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("X").x - 15.00f);
            if (ImGui::Button("X")) stateUpload = true;
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
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
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::NewLine;
            ImGui::Spacing();
            ImGui::Checkbox("Delete Origin Files?", &deleteOriginFiles);
            ImGui::End();
        }
    }

    void makeWindowDescompress() {
        if (!stateDescompact) {
            bool* p_open = NULL;
            ImGuiWindowFlags window_flags = 0;
            ImGuiIO& io = ImGui::GetIO();
            ImVec2 displaySize = io.DisplaySize;
            float windowWidth = 750.0f;
            float windowHeight = 200.0f;
            float windowPositionX = ImGui::GetWindowPos().x;
            float windowPositionY = ImGui::GetWindowPos().y;
            float windowX = ((displaySize.x - windowWidth) / 2.0f) + windowPositionX;
            float windowY = (((displaySize.y - windowHeight) / 2.0f) + windowPositionY) * 0.90f;
            window_flags |= ImGuiWindowFlags_NoTitleBar;
            window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
            window_flags |= ImGuiWindowFlags_NoMove;
            ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
            ImGui::SetNextWindowPos(ImVec2(windowX, windowY), ImGuiCond_Always);
            ImGui::SetNextWindowFocus();
            ImGui::Begin("descompactBlock", p_open, window_flags);
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("X").x - 15.00f);
            if (ImGui::Button("X")) stateDescompact = true;
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::Text("%s", "SELECT THE OUTPUT PATH:");
            ImGui::Spacing();
            ImGui::PushItemWidth(600);
            ImGui::InputText(" ", outputPath, sizeof(input));
            ImGui::PopItemWidth;
            ImGui::SameLine();
            if (ImGui::Button("Descompact")) {
                outputPathResult = string(outputPath);
                MainFrame::descompressDeleteRegister(outputPathResult, checkedFiles);
                stateDescompact = true;
            }
            if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
            ImGui::NewLine;
            ImGui::Spacing();
            ImGui::End();
        }
    }

    void menuBar()
    {
       if (ImGui::BeginMainMenuBar())
       {
           if (ImGui::Button("Descompact")) stateDescompact = false;
           if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
           if (ImGui::Button("Upload")) stateUpload = false;
           if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
           if (ImGui::Button("Delete") && checkedFiles.size() != 0) MainFrame::delteFileAndRegister(checkedFiles);
           if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
           ImGui::EndMainMenuBar();
       }
       makeWindowInput();
       makeWindowDescompress();
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

    static void loadingBar() {
        vector<int> checkedProcess = MainFrame::checkProcessing();
        if (checkedProcess[0] >= 0) {
            float floatProgress = static_cast<float>(checkedProcess[0]);
            floatProgress = floatProgress / 100;
            if (floatProgress > 100) floatProgress = 1.0f;
            string textLoading = to_string(checkedProcess[1]) + " Files processed";
            if(checkedProcess[1] > 0) ImGui::Text("%s", textLoading.c_str());
            ImGui::ProgressBar(floatProgress, ImVec2(0.0f, 0.0f), "Loading...");
        }
        
    }

    void RenderUi()
    {   
        adjustFont();
        makepWindow();
        menuBar();
        loadingBar();
        makeFiles();
        ImGui::End();
    }
}
