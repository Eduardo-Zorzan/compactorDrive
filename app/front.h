#pragma once

#include "imgui.h"
#include "stdio.h"
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <shobjidl.h>
#include <locale>
#include <codecvt>

using namespace std;

namespace MyApp {
    struct FileItem {
        string fileName;
        ImTextureID imageTexture;
    };
    static void loadingBar();
    ImTextureID LoadImage(const string filePath);
    ImGuiWindowFlags makepWindow();
    static void makeFiles();
    void menuBar();
    void adjustFont();
    void freeTexture();
    void RenderUi();
    void makeWindowInput();
    void makeWindowDescompress();
    void cleanChecked();
    string OpenFileOrFolderDialog(bool selectFolders = false);
    static void checkboxFiles(string fileName);
}

