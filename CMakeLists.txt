cmake_minimum_required(VERSION 3.12)
#-------------------------------------------------------------------------------------------
# I'm going to use vcpk in most cases for our install of 3rd party libs
# this is going to check the environment variable for CMAKE_TOOLCHAIN_FILE and this must point to where
# vcpkg.cmake is in the University this is set in your .bash_profile to
# export CMAKE_TOOLCHAIN_FILE=/public/devel/2020/vcpkg/scripts/buildsystems/vcpkg.cmake
# to build see the NGL instructions 
# Windows :- mkdir build; cd build ; cmake -DCMAKE_PREFIX_PATH=~/NGL/ .. ; cmake --build . 
# Linux / Mac mkdir build; cd build; cmake -DCMAKE_PREFIX_PATH=~/NGL/ .. ; make
#-------------------------------------------------------------------------------------------

#-------------------------------------------------------------------------------------------
# Windows compilation and linking - personal device
# mkdir build; cd build; 
# cmake -DNGL_DIR="C:\Users\ye-da\NGL" -DCMAKE_TOOLCHAIN_FILE="$HOME/Desktop/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:\Qt\5.15.18\msvc2019_64" ..
# cmake --build . 
# cd debug; $env:Path += ";C:\Qt\5.15.18\msvc2019_64\bin"
#-------------------------------------------------------------------------------------------

# Initial configuration
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

# Project name
project(ClothSimulation)
set(TargetName ClothSimulation) # This is the name of the Exe

# Find NGL
find_package(NGL CONFIG REQUIRED)

#Qt configuration 
set(CMAKE_AUTOMOC ON)
find_package(Qt6 COMPONENTS OpenGL Widgets QUIET )
if ( Qt6_FOUND )
    message("Found Qt6 Using that")
else()
    message("Found Qt5 Using that")
    find_package(Qt5 COMPONENTS OpenGL Widgets REQUIRED)
endif()

# C++ 17 configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set the name of the executable we want to build
add_executable(${TargetName})

# Add NGL include path
include_directories(include $ENV{HOME}/NGL/include)

target_sources(${TargetName} PRIVATE 
            ${PROJECT_SOURCE_DIR}/src/main.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLScene.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLSceneMouseControls.cpp
            ${PROJECT_SOURCE_DIR}/src/Mass.cpp
            ${PROJECT_SOURCE_DIR}/src/Cloth.cpp
			${PROJECT_SOURCE_DIR}/include/NGLScene.h
            ${PROJECT_SOURCE_DIR}/include/Mass.h    
            ${PROJECT_SOURCE_DIR}/include/Spring.h
            ${PROJECT_SOURCE_DIR}/include/Cloth.h    
)

target_link_libraries(${TargetName} PRIVATE Qt::Widgets Qt::OpenGL NGL)

#-------------------------------------------------------------------------------------------
# GoogleTest Config
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()

# Test Exe
add_executable(ClothSimulationTests)
target_sources(ClothSimulationTests PRIVATE 
            ${PROJECT_SOURCE_DIR}/tests/MassTest.cpp
            ${PROJECT_SOURCE_DIR}/tests/SpringTest.cpp
            ${PROJECT_SOURCE_DIR}/tests/ClothTest.cpp
            ${PROJECT_SOURCE_DIR}/src/Mass.cpp
)
target_link_libraries(ClothSimulationTests PRIVATE GTest::gtest GTest::gtest_main Qt::Widgets Qt::OpenGL NGL)
gtest_discover_tests(ClothSimulationTests)
#-------------------------------------------------------------------------------------------

#add_custom_target(${TargetName}CopyShaders ALL
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
#    $<TARGET_FILE_DIR:${TargetName}>/shaders
#)
