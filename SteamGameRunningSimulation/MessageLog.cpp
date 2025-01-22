#include "MessageLog.h"
#include "imgui.h"
#include <vector>
#include <string>

std::vector<std::pair<std::string,xLog::LogType>> logBuffer;

void xLog::AddLog(xLog::LogType logtype, std::string text)
{
    logBuffer.push_back({text,logtype});  // 添加日志到缓冲区

    // 保证日志条数不过多，避免内存溢出，限制最大条数
    if (logBuffer.size() > 1000)
    {
        logBuffer.erase(logBuffer.begin());  // 移除最旧的日志
    }
}

void xLog::ShowLogWindow()
{
    ImGui::Begin("Log Window");

    // 创建一个可以滚动的区域
    ImGui::BeginChild("LogArea", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar);
    ImVec4 red = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 orange = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x);
    // 显示日志内容
    for (const auto& logLine : logBuffer)
    {
        switch (logLine.second)
        {
        case xLog::Display:
            ImGui::TextColored(white, "%s", logLine.first.c_str());
            break;
        case xLog::Warning:
            ImGui::TextColored(orange, "%s", logLine.first.c_str());
            break;
        case xLog::Error:
            ImGui::TextColored(red, "%s", logLine.first.c_str());
            break;
        }
    }

    // 始终让滚动条滚动到底部，显示最新的日志
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);  // 设置滚动条位置为最底部
    }

    ImGui::EndChild();

    ImGui::End();
}

