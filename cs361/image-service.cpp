#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>

int main() {
    // load all image paths at startup
    std::vector<std::string> imgs;
    for (auto& entry : std::filesystem::directory_iterator("images")) {
        imgs.push_back(entry.path().string());
    }

    while (true) {
        // wait 1 second before checking the pipe
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // read the index from image-service.txt
        std::ifstream in("image-service.txt");
        int idx;
        if (!(in >> idx)) {
            in.close();
            continue;  // no valid number, skip
        }
        in.close();

        // pick a file by modulo
        int pick = idx % imgs.size();

        // clear the pipe and write the chosen path
        std::ofstream out("image-service.txt", std::ios::trunc);
        out << imgs[pick];
        out.close();
    }

    return 0;
}