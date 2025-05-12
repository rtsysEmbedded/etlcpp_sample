cmake_minimum_required(VERSION 3.10.0)
project(etlcpp_test VERSION 0.1.0 LANGUAGES C CXX)

# Enable testing options
option(TEST_BUILD "Enable building tests" ON)

# Fetch ETL library
Include(FetchContent)

FetchContent_Declare(
  etl
  GIT_REPOSITORY https://github.com/ETLCPP/etl
  GIT_TAG        20.40.0
)

FetchContent_MakeAvailable(etl)

# Include CPack for packaging
include(CPack)

# Handle building tests or main project
if (${TEST_BUILD})
    message("Building tests")
    add_subdirectory(tests)  # Add the tests directory
else()
    message("Building main project")
    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE etl::etl)
endif()
