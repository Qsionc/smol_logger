if (UNIT_TEST)
    find_package(GTest REQUIRED)
    set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
    add_executable(test_main ${TEST_DIR}/test-main.cpp)
    target_link_libraries(test_main PUBLIC
            GTest::GTest
            smogger)
endif ()