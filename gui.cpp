#include "external/imgui/imgui.h"
#include "rlImGui.h"
#include "gui.hpp"
#include <raylib.h>

namespace ui
{

void init()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT); 
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "DiskScanner");
    SetTargetFPS(144);
    rlImGuiSetup(true);
}

bool done()
{
    return WindowShouldClose();
}

void begin()
{
    BeginDrawing();
    rlImGuiBegin();
}

void end()
{
    rlImGuiEnd();
    EndDrawing();
}

}
