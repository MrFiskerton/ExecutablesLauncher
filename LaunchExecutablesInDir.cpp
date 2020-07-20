#include "LaunchExecutablesInDir.hpp"

int execute_file(const char* file) {
    pid_t  pid = fork();
    switch (pid) {
        case -1:
            std::cerr << "fork() failed!" << std::endl;
            std::exit(EXIT_FAILURE);
        case 0: // Child process
            // Making process silent
            close(1); creat("/dev/null",0644); // make stdout to go to /dev/null
            close(2); dup(1); // make stderr to go to the same file as stdout

            execl(file, file, static_cast<char*>(nullptr)); //The exec() functions return only if an error has occurred.
            std::cerr << "exec() failed!" << std::endl;
            std::exit(EXIT_FAILURE); //std::raise(SIGKILL);
    }

    // Parent process
    int status;
    waitpid(pid, &status, 0);

    if(WIFEXITED(status))
        return WEXITSTATUS(status);
    if(WIFSIGNALED(status)) {
        std::cerr << file << " killed with signal "  << WTERMSIG(status) << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return EXIT_FAILURE;
}


void launch_executables_in_dir(const fs::path &path, std::ostream& out) {
    fs::directory_entry dir(path);
    if (!dir.exists()) {
        std::cerr << "Incorrect argument, directory " << dir << " doesn't exist!" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    if (!dir.is_directory()) {
        std::cerr << "Incorrect argument, given path " << dir << " isn't a directory!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto is_executable = [](const fs::directory_entry &file) -> bool {
        // Can someone execute the file?
        constexpr auto all_exec = fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec;
        return (file.status().permissions() & all_exec) != fs::perms::none;
    };

    auto can_execute = [](const fs::directory_entry &file) -> bool {
        // Checks whether the calling process can execute the file
        return !access(file.path().c_str(), X_OK); // On success (all requested permissions granted), zero is returned
    };

    int exit_code;
    for(const auto& dir_entry: fs::recursive_directory_iterator(dir)) {
        if (!dir_entry.is_directory() && is_executable(dir_entry)) {
            if (can_execute(dir_entry)) {
                exit_code = execute_file(dir_entry.path().c_str());
                out << exit_code << "\t" << dir_entry << std::endl;
            } else {
                std::cerr << "[WARN]: Permission denied " << dir_entry << std::endl;
            }
        }
    }
}