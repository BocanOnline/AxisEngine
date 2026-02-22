cmake_minimum_required(VERSION 3.23)

project(AxisEngine CXX)

set(APP_LASER_NAME ${PROJECT_NAME}-App-Laser)
set(APP_PLOTTER_NAME ${PROJECT_NAME}-App-Plotter)
set(APP_PRINTER_NAME ${PROJECT_NAME}-App-Printer)
set(APP_ROUTER_NAME ${PROJECT_NAME}-App-Router)
set(CORE_NAME ${PROJECT_NAME}-Core)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(column_print_list TITLE LIST_VAR)
    message(STATUS "${TITLE}")
    foreach(item IN LISTS ${LIST_VAR})
        message(STATUS "${item}")
    endforeach()
endfunction()

option(BUILD_TESTING "Build Tests" ON)

if(BUILD_TESTING)
    enable_testing()
endif()

#add_subdirectory(source/${APP_LASER_NAME})
add_subdirectory(source/${APP_PLOTTER_NAME})
#add_subdirectory(source/${APP_PRINTER_NAME})
#add_subdirectory(source/${APP_ROUTER_NAME})
add_subdirectory(source/${CORE_NAME})
