cmake_minimum_required(VERSION 2.8)
set(CMAKE_INSTALL_PREFIX /usr/local)
project(gherkin_csv)
include_directories(${PROJECT_INC_DIR}/src)

set(CMAKE_C_FLAGS "-g")
file(GLOB SRC "src/*.c")
add_executable(gherkin_csv ${SRC})
target_link_libraries(gherkin_csv -ljnxc)
