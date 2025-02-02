#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <steam/steam_api.h>
#include <fstream>

int main(int argc, char* argv[]) {
    
#ifdef _DEBUG
    std::cout << "子进程启动！游戏Id : " << argv[1] << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << "参数 " << i << ": " << argv[i] << std::endl;
    }
#endif
    std::ofstream outfile;
    std::string filePath = "steam_appid.txt";
    outfile.open(filePath);
    if (!outfile)
    {
        MessageBox(NULL, L"steam_appid.txt 打开失败", L"Error", MB_ICONERROR);
        return 1;
    }
    outfile << argv[1] << std::endl;
    outfile.close();
    if ( SteamAPI_RestartAppIfNecessary( k_uAppIdInvalid  ) )
    {
        return 1;
    }
    if ( !SteamAPI_Init() )
    {
        printf( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
        return 1;
    }
    while (true)
    {
        Sleep(1000);
    }
    return 0;
}