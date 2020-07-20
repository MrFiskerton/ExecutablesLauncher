#include "gtest/gtest.h"
#include <filesystem>
#include "../LaunchExecutablesInDir.hpp"

namespace {
    fs::path root("../../test/folder");

    TEST(launch_executables_in_dir, all) {
        testing::internal::CaptureStdout();

        launch_executables_in_dir(root / "A", std::cout);

        std::string cout = testing::internal::GetCapturedStdout();
        std::string correct_cout = "0\t\"../../test/folder/A/B/ls\"\n1\t\"../../test/folder/A/empty_executable\"\n42\t\"../../test/folder/A/return_42\"\n0\t\"../../test/folder/A/Hello_my_PID\"\n";
        ASSERT_EQ(cout, correct_cout);
    }

    TEST(launch_executables_in_dir, signal) {
        testing::internal::CaptureStderr();

        //EXPECT_EXIT(launch_executables_in_dir(root / "level_1/level_2/level_3", std::cout),testing::ExitedWithCode(1), "message1");

        std::string cerr = testing::internal::GetCapturedStderr();
        std::string correct_cerr = "";
        ASSERT_EQ(cerr, correct_cerr);
    }
}