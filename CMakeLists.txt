#______                            ______                  
#|  _  \                           | ___ \                 
#| | | |_ __ __ _  __ _  ___  _ __ | |_/ /_   _ _ __ _ __  
#| | | | '__/ _` |/ _` |/ _ \| '_ \| ___ \ | | | '__| '_ \ 
#| |/ /| | | (_| | (_| | (_) | | | | |_/ / |_| | |  | | | |
#|___/ |_|  \__,_|\__, |\___/|_| |_\____/ \__,_|_|  |_| |_|
#                  __/ |                                   
#                 |___/             
#                        
#https://github.com/ByteCorum/DragonBurn

# Minimum required CMake version
cmake_minimum_required(VERSION 3.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /MT /D NDEBUG")

# Project name
project(DragonBurn)

#Target dir
set_target_properties(DragonBurn PROPERTIES
    OUTPUT_NAME "DragonBurn"
    RUNTIME_OUTPUT_DIRECTORY "built")

# Include Directories
set(INCLUDE_DIRS
  Config
  Core
  Features
  Game
  Helpers
  Offsets
  OS-ImGui/imgui
  OS-ImGui
  Resources
  Libs/json
)

# Add an executable from source files
add_executable(DragonBurn
    DragonBurn/main.cpp
    DragonBurn/Config/ConfigMenu.cpp
    DragonBurn/Config/ConfigMenu.hpp
    DragonBurn/Config/ConfigSaver.cpp
    DragonBurn/Config/ConfigSaver.hpp
    DragonBurn/Config/MenuConfig.hpp
    DragonBurn/DragonBurn/Core/Cheats.cpp
    DragonBurn/Core/Cheats.h
    DragonBurn/Core/Globals.hpp
    DragonBurn/Core/GlobalVars.cpp
    DragonBurn/Core/GlobalVars.h
    DragonBurn/Core/GUI.h
    DragonBurn/Core/Init.h
    DragonBurn/Core/ProcessManager.hpp
    DragonBurn/Core/Render.hpp
    DragonBurn/Features/Aimbot.cpp
    DragonBurn/Features/Aimbot.h
    DragonBurn/Features/BombTimer.h
    DragonBurn/Features/ESP.h
    DragonBurn/Features/Misc.cpp
    DragonBurn/Features/Misc.h
    DragonBurn/Features/Radar.cpp
    DragonBurn/Features/Radar.h
    DragonBurn/DragonBurn/Features/RCS.h
    DragonBurn/DragonBurn/Features/RCS.cpp
    DragonBurn/Features/SpectatorList.h
    DragonBurn/Features/TriggerBot.cpp
    DragonBurn/Features/TriggerBot.h
    DragonBurn/Game/Bone.cpp
    Game/Bone.h
    DragonBurn/Game/Entity.cpp
    DragonBurn/Game/Entity.h
    DragonBurn/Game/Game.cpp
    DragonBurn/Game/Game.h
    DragonBurn/Game/View.hpp
    DragonBurn/Helpers/Format.h
    DragonBurn/Helpers/GetWeaponIcon.h
    DragonBurn/Helpers/Mouse.cpp
    DragonBurn/Helpers/Mouse.h
    DragonBurn/Helpers/Random.h
    DragonBurn/Libs/json.hpp
    DragonBurn/Offsets/Offsets.h
    DragonBurn/Offsets/Offsets.cpp
    DragonBurn/OS-ImGui/OS-ImGui.cpp
    DragonBurn/OS-ImGui/OS-ImGui.h
    DragonBurn/OS-ImGui/OS-ImGui_Base.cpp
    DragonBurn/OS-ImGui/OS-ImGui_Base.h
    DragonBurn/OS-ImGui/OS-ImGui_Exception.hpp
    DragonBurn/OS-ImGui/OS-ImGui_External.cpp
    DragonBurn/OS-ImGui/OS-ImGui_External.h
    DragonBurn/OS-ImGui/OS-ImGui_Struct.h
    DragonBurn/OS-ImGui/imgui/imconfig.h
    DragonBurn/OS-ImGui/imgui/imgui.cpp
    DragonBurn/OS-ImGui/imgui/imgui.h
    DragonBurn/OS-ImGui/imgui/imgui_demo.cpp
    DragonBurn/OS-ImGui/imgui/imgui_draw.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.h
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.h
    DragonBurn/OS-ImGui/imgui/imgui_internal.h
    DragonBurn/OS-ImGui/imgui/imgui_tables.cpp
    DragonBurn/OS-ImGui/imgui/imgui_widgets.cpp
    DragonBurn/OS-ImGui/imgui/imstb_rectpack.h
    DragonBurn/OS-ImGui/imgui/imstb_textedit.h
    DragonBurn/OS-ImGui/imgui/imstb_truetype.h
    DragonBurn/OS-ImGui/stb/stb_image.h
    DragonBurn/Resources/font.h
    DragonBurn/Resources/Images.h
    DragonBurn/Resources/Language.h
    DragonBurn/Resources/Sounds.h
    DragonBurn/Resources/WeaponIcon.h
    DragonBurn/main.cpp
    DragonBurn/Config/ConfigMenu.cpp
    DragonBurn/Config/ConfigMenu.hpp
    DragonBurn/Config/ConfigSaver.cpp
    DragonBurn/Config/ConfigSaver.hpp
    DragonBurn/Config/MenuConfig.hpp
    DragonBurn/DragonBurn/Core/Cheats.cpp
    DragonBurn/Core/Cheats.h
    DragonBurn/Core/Globals.hpp
    DragonBurn/Core/GlobalVars.cpp
    DragonBurn/Core/GlobalVars.h
    DragonBurn/Core/GUI.h
    DragonBurn/Core/Init.h
    DragonBurn/Core/ProcessManager.hpp
    DragonBurn/Core/Render.hpp
    DragonBurn/Features/Aimbot.cpp
    DragonBurn/Features/Aimbot.h
    DragonBurn/Features/BombTimer.h
    DragonBurn/Features/ESP.h
    DragonBurn/Features/Misc.cpp
    DragonBurn/Features/Misc.h
    DragonBurn/Features/Radar.cpp
    DragonBurn/Features/Radar.h
    DragonBurn/DragonBurn/Features/RCS.h
    DragonBurn/DragonBurn/Features/RCS.cpp
    DragonBurn/Features/SpectatorList.h
    DragonBurn/Features/TriggerBot.cpp
    DragonBurn/Features/TriggerBot.h
    DragonBurn/Game/Bone.cpp
    Game/Bone.h
    DragonBurn/Game/Entity.cpp
    DragonBurn/Game/Entity.h
    DragonBurn/Game/Game.cpp
    DragonBurn/Game/Game.h
    DragonBurn/Game/View.hpp
    DragonBurn/Helpers/Format.h
    DragonBurn/Helpers/GetWeaponIcon.h
    DragonBurn/Helpers/Mouse.cpp
    DragonBurn/Helpers/Mouse.h
    DragonBurn/Helpers/Random.h
    DragonBurn/Libs/json.hpp
    DragonBurn/Offsets/Offsets.h
    DragonBurn/Offsets/Offsets.cpp
    DragonBurn/OS-ImGui/OS-ImGui.cpp
    DragonBurn/OS-ImGui/OS-ImGui.h
    DragonBurn/OS-ImGui/OS-ImGui_Base.cpp
    DragonBurn/OS-ImGui/OS-ImGui_Base.h
    DragonBurn/OS-ImGui/OS-ImGui_Exception.hpp
    DragonBurn/OS-ImGui/OS-ImGui_External.cpp
    DragonBurn/OS-ImGui/OS-ImGui_External.h
    DragonBurn/OS-ImGui/OS-ImGui_Struct.h
    DragonBurn/OS-ImGui/imgui/imconfig.h
    DragonBurn/OS-ImGui/imgui/imgui.cpp
    DragonBurn/OS-ImGui/imgui/imgui.h
    DragonBurn/OS-ImGui/imgui/imgui_demo.cpp
    DragonBurn/OS-ImGui/imgui/imgui_draw.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.h
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.h
    DragonBurn/OS-ImGui/imgui/imgui_internal.h
    DragonBurn/OS-ImGui/imgui/imgui_tables.cpp
    DragonBurn/OS-ImGui/imgui/imgui_widgets.cpp
    DragonBurn/OS-ImGui/imgui/imstb_rectpack.h
    DragonBurn/OS-ImGui/imgui/imstb_textedit.h
    DragonBurn/OS-ImGui/imgui/imstb_truetype.h
    DragonBurn/OS-ImGui/stb/stb_image.h
    DragonBurn/Resources/font.h
    DragonBurn/Resources/Images.h
    DragonBurn/Resources/Language.h
    DragonBurn/Resources/Sounds.h
    DragonBurn/Resources/WeaponIcon.h
    DragonBurn/main.cpp
    DragonBurn/Config/ConfigMenu.cpp
    DragonBurn/Config/ConfigMenu.hpp
    DragonBurn/Config/ConfigSaver.cpp
    DragonBurn/Config/ConfigSaver.hpp
    DragonBurn/Config/MenuConfig.hpp
    DragonBurn/DragonBurn/Core/Cheats.cpp
    DragonBurn/Core/Cheats.h
    DragonBurn/Core/Globals.hpp
    DragonBurn/Core/GlobalVars.cpp
    DragonBurn/Core/GlobalVars.h
    DragonBurn/Core/GUI.h
    DragonBurn/Core/Init.h
    DragonBurn/Core/ProcessManager.hpp
    DragonBurn/Core/Render.hpp
    DragonBurn/Features/Aimbot.cpp
    DragonBurn/Features/Aimbot.h
    DragonBurn/Features/BombTimer.h
    DragonBurn/Features/ESP.h
    DragonBurn/Features/Misc.cpp
    DragonBurn/Features/Misc.h
    DragonBurn/Features/Radar.cpp
    DragonBurn/Features/Radar.h
    DragonBurn/DragonBurn/Features/RCS.h
    DragonBurn/DragonBurn/Features/RCS.cpp
    DragonBurn/Features/SpectatorList.h
    DragonBurn/Features/TriggerBot.cpp
    DragonBurn/Features/TriggerBot.h
    DragonBurn/Game/Bone.cpp
    Game/Bone.h
    DragonBurn/Game/Entity.cpp
    DragonBurn/Game/Entity.h
    DragonBurn/Game/Game.cpp
    DragonBurn/Game/Game.h
    DragonBurn/Game/View.hpp
    DragonBurn/Helpers/Format.h
    DragonBurn/Helpers/GetWeaponIcon.h
    DragonBurn/Helpers/Mouse.cpp
    DragonBurn/Helpers/Mouse.h
    DragonBurn/Helpers/Random.h
    DragonBurn/Libs/json.hpp
    DragonBurn/Offsets/Offsets.h
    DragonBurn/Offsets/Offsets.cpp
    DragonBurn/OS-ImGui/OS-ImGui.cpp
    DragonBurn/OS-ImGui/OS-ImGui.h
    DragonBurn/OS-ImGui/OS-ImGui_Base.cpp
    DragonBurn/OS-ImGui/OS-ImGui_Base.h
    DragonBurn/OS-ImGui/OS-ImGui_Exception.hpp
    DragonBurn/OS-ImGui/OS-ImGui_External.cpp
    DragonBurn/OS-ImGui/OS-ImGui_External.h
    DragonBurn/OS-ImGui/OS-ImGui_Struct.h
    DragonBurn/OS-ImGui/imgui/imconfig.h
    DragonBurn/OS-ImGui/imgui/imgui.cpp
    DragonBurn/OS-ImGui/imgui/imgui.h
    DragonBurn/OS-ImGui/imgui/imgui_demo.cpp
    DragonBurn/OS-ImGui/imgui/imgui_draw.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.h
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.h
    DragonBurn/OS-ImGui/imgui/imgui_internal.h
    DragonBurn/OS-ImGui/imgui/imgui_tables.cpp
    DragonBurn/OS-ImGui/imgui/imgui_widgets.cpp
    DragonBurn/OS-ImGui/imgui/imstb_rectpack.h
    DragonBurn/OS-ImGui/imgui/imstb_textedit.h
    DragonBurn/OS-ImGui/imgui/imstb_truetype.h
    DragonBurn/OS-ImGui/stb/stb_image.h
    DragonBurn/Resources/font.h
    DragonBurn/Resources/Images.h
    DragonBurn/Resources/Language.h
    DragonBurn/Resources/Sounds.h
    DragonBurn/Resources/WeaponIcon.h
)

# Include OS-ImGui headers
include_directories(${OS-ImGui_INCLUDE_DIRS})

# Linking with JSON
include_directories(${json_INCLUDE_DIRS})

# Target Executable
add_executable(DragonBurn ${SOURCE_FILES})

target_sources(DragonBurn
    PRIVATE
        DragonBurn/AssemblyInfo.rc)

add_custom_command(
    OUTPUT AssemblyInfo.res
    COMMAND windres DragonBurn/AssemblyInfo.rc
    OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
link_directories(${CMAKE_CURRENT_BINARY_DIR})


cmake_minimum_required(VERSION 3.10)

# Set the project name
project(DragonBurnProject)

# Add the executable for DragonBurn
add_executable(DragonBurn
    DragonBurn/main.cpp
    DragonBurn/Config/ConfigMenu.cpp
    DragonBurn/Config/ConfigSaver.cpp
    DragonBurn/Core/Cheats.cpp
    DragonBurn/Core/GlobalVars.cpp
    DragonBurn/Core/MemoryMgr.cpp
    DragonBurn/Features/Aimbot.cpp
    DragonBurn/Features/Misc.cpp
    DragonBurn/Features/Radar.cpp
    DragonBurn/Features/RCS.cpp
    DragonBurn/Features/TriggerBot.cpp
    DragonBurn/Game/Bone.cpp
    DragonBurn/Game/Entity.cpp
    DragonBurn/Game/Game.cpp
    DragonBurn/Helpers/Mouse.cpp
    DragonBurn/Offsets/Offsets.cpp
    DragonBurn/OS-ImGui/OS-ImGui.cpp
    DragonBurn/OS-ImGui/OS-ImGui_Base.cpp
    DragonBurn/OS-ImGui/OS-ImGui_External.cpp
    DragonBurn/OS-ImGui/imgui/imgui.cpp
    DragonBurn/OS-ImGui/imgui/imgui_demo.cpp
    DragonBurn/OS-ImGui/imgui/imgui_draw.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_dx11.cpp
    DragonBurn/OS-ImGui/imgui/imgui_impl_win32.cpp
    DragonBurn/OS-ImGui/imgui/imgui_tables.cpp
    DragonBurn/OS-ImGui/imgui/imgui_widgets.cpp
    DragonBurn/Resources/Resource.rc
)

# Add the icon to the executable
set_source_files_properties(DragonBurn/icon.ico PROPERTIES HEADER_FILE_ONLY TRUE)
target_sources(DragonBurn PRIVATE DragonBurn/icon.ico)

# Add the driver for DragonBurn-kernel
add_library(DragonBurn-kernel MODULE
    DragonBurn-kernel/main.c
    DragonBurn-kernel/Functions.c
    DragonBurn-kernel/Memory.c
    DragonBurn-kernel/Resource.rc
)

# Set properties for the driver
set_target_properties(DragonBurn-kernel PROPERTIES
    OUTPUT_NAME "DragonBurn-kernel"
    SUFFIX ".sys"
)

# Include directories
target_include_directories(DragonBurn PRIVATE
    DragonBurn/Config
    DragonBurn/Core
    DragonBurn/Features
    DragonBurn/Game
    DragonBurn/Helpers
    DragonBurn/Offsets
    DragonBurn/OS-ImGui
    DragonBurn/OS-ImGui/imgui
    DragonBurn/OS-ImGui/stb
    DragonBurn/Resources
    DragonBurn/Libs/json  # Include the JSON library directory
)

target_include_directories(DragonBurn-kernel PRIVATE
    DragonBurn-kernel
)


