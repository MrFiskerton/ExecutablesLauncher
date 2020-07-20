#include <thread>

int main(int argc, const char* argv[]) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
