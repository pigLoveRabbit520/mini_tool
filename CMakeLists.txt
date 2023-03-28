cmake_minimum_required(VERSION 3.2)

SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)

project(mini_tool)

aux_source_directory(src SOURCE)

set(wxWidgets_ROOT_DIR $ENV{WXWIN})
set(wxWidgets_LIB_DIR $ENV{WXWIN}/lib/gcc_lib)
set(wxWidgets_CONFIGURATION mswu)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS_RELEASE, "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG") # 优化编译

add_executable(${PROJECT_NAME} WIN32 ${SOURCE})
find_package(wxWidgets COMPONENTS net core base)
if(wxWidgets_FOUND)
  include(${wxWidgets_USE_FILE})
  target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif()