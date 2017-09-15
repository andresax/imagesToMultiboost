cmake_minimum_required(VERSION 2.8.3)

project(imageToMultiboost)

#----------------------- CMAKE MODULES ------------------------

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules) 
 
# ----------------------- LIBRARIES ---------------------------
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(OpenCV REQUIRED)

MESSAGE( STATUS "CMAKE_BUILD_TYPE:      " ${CMAKE_BUILD_TYPE} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -frounding-math  ")
# ----------------------- INCLUDES ----------------------------
include_directories(  ${OpenCV_INCLUDE_DIRS}
                      include/imageToMultiboost)
# ----------------------- GCC FLAGS ----------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# ------------------------ BUILD -------------------------------
 
file(GLOB_RECURSE imageToMultiboost_src
                  src/*.cpp)

add_executable(imageToMultiboost ${imageToMultiboost_src} )
target_link_libraries(imageToMultiboost ${OpenCV_LIBS}
                                        ${Boost_LIBRARIES} )

