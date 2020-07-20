#include "LaunchExecutablesInDir.hpp"

int main(int argc, const char* argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect argument, usage: " << argv[0] << " \"path/to/directory\"" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const auto dir_path = fs::path{ argv[1] };
    launch_executables_in_dir(dir_path, std::cout);
    return EXIT_SUCCESS;
}