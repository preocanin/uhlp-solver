find_package(GTest)
include(GoogleTest)

add_executable(tests main.cpp)

target_link_libraries(tests
    PRIVATE
    GTest::GTest
    ${PROJECT_NAME}_lib)

gtest_discover_tests(tests)
