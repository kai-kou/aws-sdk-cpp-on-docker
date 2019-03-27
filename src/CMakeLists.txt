cmake_minimum_required(VERSION 3.5)

find_package(AWSSDK REQUIRED COMPONENTS s3)

add_definitions(-DUSE_IMPORT_EXPORT)

add_executable(main main.cpp)

target_link_libraries(main ${AWSSDK_LINK_LIBRARIES})
