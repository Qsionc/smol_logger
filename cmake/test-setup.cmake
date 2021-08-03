if (UNIT_TEST)
    add_executable(test_main test/test-main.cpp)
    target_link_libraries(test_main PUBLIC GTest::GTest smogger)
endif ()