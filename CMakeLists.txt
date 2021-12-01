# CMakeList.txt : CMake project for TankGame, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("TankGame")

# Add source to this project's executable.
add_executable (TankGame "TankGame.cpp" "TankGame.h" "PrettyConsole/console.h" "PrettyConsole/console.cpp" "PrettyConsole/row.h" "PrettyConsole/row.cpp" "PrettyConsole/styles.h" "PrettyConsole/styles.cpp" "PrettyConsole/styleAttribute.h" "PrettyConsole/styleAttribute.cpp" "PrettyConsole/screenComponent.h" "PrettyConsole/screenComponent.cpp" "PrettyConsole/rectangle.h" "PrettyConsole/rectangle.cpp" "PrettyConsole/line.h" "PrettyConsole/line.cpp" "PrettyConsole/point.h" "PrettyConsole/point.cpp")

# TODO: Add tests and install targets if needed.
