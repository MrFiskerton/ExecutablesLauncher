#include <csignal>

int main(int argc, const char* argv[]) {
    raise(SIGINT);
}
