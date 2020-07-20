#ifndef EXECUTABLESLAUNCHER_LAUNCHEXECUTABLESINDIR_HPP
#define EXECUTABLESLAUNCHER_LAUNCHEXECUTABLESINDIR_HPP

#include <iostream>
#include <filesystem>
#include <functional>
#include <cstdlib>
#include <csignal>
#include <cassert>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

namespace fs = std::filesystem;

int execute_file(const char* file);
void launch_executables_in_dir(const fs::path &path, std::ostream& out);

#endif //EXECUTABLESLAUNCHER_LAUNCHEXECUTABLESINDIR_HPP
