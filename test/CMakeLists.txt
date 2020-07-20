add_executable(runUnitTests run_test.cpp ../LaunchExecutablesInDir.cpp)

target_link_libraries(runUnitTests gtest gtest_main pthread)

add_test(
        NAME runUnitTests
        COMMAND runUnitTests
)