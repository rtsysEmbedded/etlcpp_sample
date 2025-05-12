cmake_minimum_required(VERSION 3.5.0)
project(etl_unit_tests LANGUAGES CXX)

# Enable testing framework
enable_testing()

# Add UnitTest++ as a submodule or fetch it via FetchContent
# Using FetchContent to get UnitTest++
Include(FetchContent)

FetchContent_Declare(
    UnitTest++
    GIT_REPOSITORY https://github.com/unittest-cpp/unittest-cpp
    GIT_TAG v2.0.0
)

FetchContent_MakeAvailable(UnitTest++)

# Add test executable
add_executable(${PROJECT_NAME} test.cpp)

# Link dependencies
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/  # To find headers in the main project
    ${UnitTest++_SOURCE_DIR} # To find UnitTest++ headers
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    UnitTest++ 
    etl::etl # Link the ETL library
)

# Register the test with CTest
add_test(NAME packet_buffer_test COMMAND ${PROJECT_NAME})
