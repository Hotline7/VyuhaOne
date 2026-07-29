add_executable(vyuhaone_tests
    src/test_position.cpp
)

target_link_libraries(vyuhaone_tests
    PRIVATE
        vyuhaone_engine
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(vyuhaone_tests)