#include "gtest/gtest.h"
#include <filesystem>
#include "../LaunchExecutablesInDir.hpp"

namespace {
    fs::path test_root_folder("../../test/folder");

    TEST(launch_executables_in_dir, complex_test) {
        testing::internal::CaptureStdout();

        launch_executables_in_dir(test_root_folder / "A", std::cout);

        std::string cout = testing::internal::GetCapturedStdout();
        std::string correct_cout = "0\t\"../../test/folder/A/B/ls\"\n1\t\"../../test/folder/A/empty_executable\"\n42\t\"../../test/folder/A/return_42\"\n0\t\"../../test/folder/A/Hello_my_PID\"\n";
        ASSERT_EQ(cout, correct_cout);
    }

    TEST(launch_executables_in_dir, empty_folder) {
        testing::internal::CaptureStdout();

        launch_executables_in_dir(test_root_folder / "empty_folder", std::cout);

        std::string cout = testing::internal::GetCapturedStdout();
        ASSERT_EQ(cout, "");
    }

    TEST(launch_executables_in_dir, raise_signal) {
        EXPECT_EXIT(launch_executables_in_dir(test_root_folder / "level_1/level_2/level_3", std::cout),
                testing::ExitedWithCode(EXIT_FAILURE), "killed with signal");
    }

    TEST(launch_executables_in_dir, incorrect_argument_not_dir) {
        EXPECT_EXIT(launch_executables_in_dir(test_root_folder / "empty_non_executable", std::cout),
                    testing::ExitedWithCode(EXIT_FAILURE), "isn't a directory!");
    }

    TEST(launch_executables_in_dir, incorrect_argument_dir_does_not_exist) {
        EXPECT_EXIT(launch_executables_in_dir(test_root_folder / "MAGIC", std::cout),
                    testing::ExitedWithCode(EXIT_FAILURE), "doesn't exist!");
    }
}