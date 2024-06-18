# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.23.0-rc1)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(cpr-populate NONE)


# Pass through things we've already detected in the main project to avoid
# paying the cost of redetecting them again in ExternalProject_Add()
set(GIT_EXECUTABLE [==[GIT_EXECUTABLE-NOTFOUND]==])
set(GIT_VERSION_STRING [==[]==])
set_property(GLOBAL PROPERTY _CMAKE_FindGit_GIT_EXECUTABLE_VERSION
  [==[GIT_EXECUTABLE-NOTFOUND;]==]
)


include(ExternalProject)
ExternalProject_Add(cpr-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/libcpr/cpr.git" "GIT_TAG" "67e12da316754ff3c6c91b50aafb2658438f3c1e"
                    SOURCE_DIR          "/mnt/c/Users/BenCarter/Documents/Bens Work/Coding/C++/TankGame/_deps/cpr-src"
                    BINARY_DIR          "/mnt/c/Users/BenCarter/Documents/Bens Work/Coding/C++/TankGame/_deps/cpr-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


