include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmakeRC.cmake")

cmake_minimum_required(VERSION 3.16)
project(course_ui)

set(CMAKE_CXX_STANDARD 20)

cmrc_add_resource_library(html_resources ALIAS html::rc NAMESPACE html "${CMAKE_CURRENT_SOURCE_DIR}/index.html")

add_executable(course_ui src/main.cpp src/managers/CourseManager.cpp src/managers/CourseManager.h src/managers/StudentManager.cpp src/managers/StudentManager.h src/html_file.h)
target_link_libraries(course_ui PRIVATE html::rc)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBVIEW_COCOA -Wall -Wextra -pedantic")
    set_target_properties(course_ui PROPERTIES LINK_FLAGS "-framework Webkit")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
#    add_library(WebView2Loader STATIC IMPORTED )
#    set_property(TARGET WebView2Loader PROPERTY IMPORTED_LOCATION ${install_dir}/dll/WebView2Loader.dll)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    #
endif ()

