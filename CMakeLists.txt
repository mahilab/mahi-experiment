# initialize required cmake options
cmake_minimum_required(VERSION 3.13)
project(experiment_project)

# get the relevant libraries to use from github. FetchContent is great because it pulls the most recent version of a library and will add it to your project.
include(FetchContent)
FetchContent_Declare(mahi-util GIT_REPOSITORY https://github.com/mahilab/mahi-util.git)
FetchContent_MakeAvailable(mahi-util)

# add the include directory for compiler and to add intellisense capabilities
include_directories(include)

# create your executable and link it to the libraries you want to use
add_executable(experiment src/experiment.cpp src/ExperimentHelper.cpp)
target_link_libraries(experiment mahi::util)

add_subdirectory(test)