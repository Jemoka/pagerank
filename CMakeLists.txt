cmake_minimum_required(VERSION 3.13)  # CMake version check
project(pagerank)                           # Create project "simple_example"
set(CMAKE_CXX_STANDARD 20)            # Enable c++20 standard

# Get header files
file(GLOB_RECURSE HEADER
    "src/*.hpp")

# Get source files
file(GLOB_RECURSE SRC
    "src/*.cpp") 

# Find eigen
find_path(EIGEN_INCLUDE_DIR Eigen/Eigen)
find_package (Eigen3 3.4 REQUIRED NO_MODULE)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(pagerank main.cpp ${SRC})

# Link eigen
target_link_libraries (pagerank Eigen3::Eigen)
target_include_directories (pagerank PRIVATE ${HEADER} ${EIGEN_INCLUDE_DIR})


# Create the run command for cmake
add_custom_target(run
  COMMAND pagerank
  DEPENDS pagerank
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})
