# CMakeList.txt : CMake project for TankGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("TankGame")
add_executable(TankGame "TankGame.cpp" "TankGame.h" "PrettyConsole/console.h" "PrettyConsole/console.cpp" "PrettyConsole/row.h" "PrettyConsole/row.cpp" "PrettyConsole/styles.h" "PrettyConsole/styles.cpp" "PrettyConsole/styleAttribute.h" "PrettyConsole/styleAttribute.cpp" "PrettyConsole/screenComponent.h" "PrettyConsole/screenComponent.cpp" "PrettyConsole/rectangle.h" "PrettyConsole/rectangle.cpp" "PrettyConsole/line.h" "PrettyConsole/line.cpp" "PrettyConsole/point.h" "PrettyConsole/point.cpp" "KeyboardListener.h" "KeyboardListener.cpp" "Stack.h"   "WindowScaler.cpp" "GameContainer.h" "GameContainer.cpp" "Player.cpp" "Tank.h" "Tank.cpp" "Weapon.h" "Shot.h" "Shot.cpp" "CPUPlayer.h" "CPUPlayer.cpp" "HumanPlayer.cpp" "HumanPlayer.h" "Stash.h" "Stash.cpp" "Weapon.cpp")

#add_subdirectory(cpr)
#include_directories(${CPR_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG 67e12da316754ff3c6c91b50aafb2658438f3c1e) # the commit hash for 1.7.0
FetchContent_MakeAvailable(cpr)

target_link_libraries(TankGame PRIVATE cpr::cpr)

# Add source to this project's executable.
# add_executable (TankGame "TankGame.cpp" "TankGame.h")
#"PrettyConsole/console.h" "PrettyConsole/console.cpp" "PrettyConsole/row.h" "PrettyConsole/row.cpp" "PrettyConsole/styles.h" "PrettyConsole/styles.cpp" "PrettyConsole/styleAttribute.h" "PrettyConsole/styleAttribute.cpp" "PrettyConsole/screenComponent.h" "PrettyConsole/screenComponent.cpp" "PrettyConsole/rectangle.h" "PrettyConsole/rectangle.cpp" "PrettyConsole/line.h" "PrettyConsole/line.cpp" "PrettyConsole/point.h" "PrettyConsole/point.cpp" "include/cpr/cpr.h" "include/curl/curl.h")


# TODO: Add tests and install targets if needed.
