#pragma once
#include <string>

namespace xLog
{
    enum LogType
    {
        Display = 0,
        Warning = 1,
        Error = 2,
    };
    
    void AddLog(xLog::LogType logtype,std::string text);
    void ShowLogWindow();
}

