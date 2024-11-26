cmake_minimum_required(VERSION 3.10)
project(test)

# 查找 SDL2 库
find_package(SDL2 REQUIRED)
find_library(SDL2_MIXER_LIBRARY SDL2_mixer REQUIRED)

# 查找 OpenCV
find_package(OpenCV REQUIRED)

# 包含头文件路径
include_directories(${SDL2_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

# 添加可执行文件
add_executable(test main.cpp)

# 链接库
target_link_libraries(test ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARY} ${OpenCV_LIBS})