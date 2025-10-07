#include <fstream>
#include <random>
#include <string>
#include <thread>
#include <chrono>

int main() {
    // random generator setup
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 100);  // random numbers 0–100

    while (true) {
        // sleep for 1 second before checking for “run”
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // open prng-service.txt to see if it says “run”
        std::ifstream in("prng-service.txt");
        std::string line;
        std::getline(in, line);
        in.close();

        // if we got “run”, generate a new random number
        if (line == "run") {
            int rnd = dist(gen);

            // clear the file and write the random number
            std::ofstream out("prng-service.txt", std::ios::trunc);
            out << rnd;
            out.close();
        }
    }

    return 0;
}