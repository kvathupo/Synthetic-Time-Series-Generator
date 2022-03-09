#include <iostream>
#include <string>
#include <unordered_map>
#include "augment.h"

int main() {
    std::string dir_path, csv_path, first_letter;


    dir_path = "./Datasets/Daily/Train/";
    first_letter = "D";
    for (auto i = 146; i < 4227 + 1; i++) {
        // augmenting data
        csv_path = dir_path + first_letter + std::to_string(i) + ".csv";
        aug::augment_data(csv_path);
        std::cout << "Done " << csv_path << std::endl;
    }

    return 0;
}
