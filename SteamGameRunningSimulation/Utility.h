#pragma once

#include <fstream>
#include <windows.h>
#include <shlobj.h> // 用于 SHGetFolderPath
#include <iostream>
#include <string>
#include <vector>

// 获取桌面路径
inline std::wstring GetDesktopPath() {
    wchar_t desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_DESKTOP, NULL, 0, desktopPath))) {
        return std::wstring(desktopPath);
    }
    return L"";
}

// 搜索桌面上的 .url 文件
inline std::vector<std::wstring> SearchUrlFilesOnDesktop() {
    std::vector<std::wstring> urlFiles;
    std::wstring desktopPath = GetDesktopPath();

    if (desktopPath.empty()) {
        std::wcerr << L"无法获取桌面路径" << std::endl;
        return urlFiles;
    }

    // 遍历桌面目录
    std::wstring searchPath = desktopPath + L"\\*.url";
    WIN32_FIND_DATAW findFileData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::wcerr << L"未找到.url文件" << std::endl;
        return urlFiles;
    }

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // 找到 .url 文件
            std::wstring fileName = findFileData.cFileName;
            urlFiles.push_back(desktopPath + L"\\" + fileName);
        }
    } while (FindNextFileW(hFind, &findFileData) != 0);

    FindClose(hFind);
    return urlFiles;
}

// 从 .url 文件中提取 URL
inline std::string ExtractUrlFromFile(const std::wstring& filePath) {
    std::ifstream file(filePath); // 打开文件
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filePath.c_str() << std::endl;
        return "";
    }

    std::string line;
    while (std::getline(file, line)) {
        // 查找以 "URL=" 开头的行
        if (line.find("URL=") == 0) {
            // 提取 URL 部分
            return line.substr(4); // 去掉 "URL="
        }
    }

    std::cerr << "未找到 URL 信息" << std::endl;
    return "";
}