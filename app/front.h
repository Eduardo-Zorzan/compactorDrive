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
#include <cmath>

using namespace std;

namespace MyApp {
    struct FileItem {
        string fileName;
        ImTextureID imageTexture;
    };
    ImTextureID LoadImage(const string filePath);
    ImGuiWindowFlags makepWindow();
    static void makeFiles();
    void DrawLoadingSpinner(float radius, int segments, float speed);
    void menuBar();
    void adjustFont();
    void freeTexture();
    void RenderUi();
    void makeWindowInput();
    void makeWindowDescompress();
    void cleanChecked();
    vector<string> OpenFileOrFolderDialog(bool selectFolders, bool allowMultipleFiles);
    static void checkboxFiles(string fileName);
}

