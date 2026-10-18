add_library(rlimgui STATIC)
target_include_directories(rlimgui
    PUBLIC
    external/rlImGui 
)
target_sources(rlimgui
    PRIVATE
        external/rlImGui/rlImGui.cpp
)
target_link_libraries(rlimgui
    PUBLIC 
        imgui
        raylib
)
