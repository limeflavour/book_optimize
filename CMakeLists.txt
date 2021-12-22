cmake_minimum_required(VERSION 3.19)
project(book_optimize)

set(CMAKE_CXX_STANDARD 11)

set(Boost_LIBRARY_DIR D:/mingwBoost169jingtai/lib)
set(Boost_INCLUDE_DIR D:/boost_1_69_0/boost_1_69_0)

set(OpenCV_INCLUDE_DIR D:/opencv330/opencv/sources/include)
set(OpenCV_LIBRARY_DIR D:/opencv330/opencv/clion64withCon/lib)

#find_package(Boost COMPONENTS regex REQUIRED)

#if(Boost_FOUND)
#    include_directories(${Boost_INCLUDE_DIRS})

#    MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
#    MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
#    MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}")

#   add_executable(book_optimize main.cpp)
#   target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})
#   target_link_libraries(book_optimize ${Boost_LIBRARIES})
#endif()

add_executable(book_optimize main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC
        ${Boost_LIBRARY_DIR}/libboost_regex-mgw49-mt-x64-1_69.a
        ${OpenCV_LIBRARY_DIR}/libopencv_core330.dll.a)

