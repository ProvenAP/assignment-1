#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

int main() {
    while (true) {
        // prompt user: 1 to show image, 2 to exit
        std::cout << "Enter 1 to get an image, 2 to quit: ";
        int choice;
        std::cin >> choice;

        if (choice == 2) {
            // clean exit
            std::cout << "Goodbye!\n";
            return 0;
        }
        else if (choice != 1) {
            // invalid input handling
            std::cout << "Unknown option. Try again.\n\n";
            continue;
        }

        // step 1: trigger PRNG
        {
            std::ofstream out("prng-service.txt", std::ios::trunc);
            out << "run";
        }

        // wait for PRNG to write a number
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // step 2: read the random number
        int rnd;
        {
            std::ifstream in("prng-service.txt");
            in >> rnd;
        }

        // step 3: send number to Image Service
        {
            std::ofstream out("image-service.txt", std::ios::trunc);
            out << rnd;
        }

        // wait for Image Service to write the path
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // step 4: read and display image path
        {
            std::ifstream in("image-service.txt");
            std::string path;
            std::getline(in, path);
            std::cout << "Selected: " << path << "\n\n";
        }
    }
    return 0;
}