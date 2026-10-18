add_library(imgui STATIC)
target_include_directories(imgui
    PUBLIC
        external/imgui
)
target_sources(imgui
    PRIVATE
        external/imgui/imgui.cpp
        external/imgui/imgui_demo.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/imgui_widgets.cpp
)
