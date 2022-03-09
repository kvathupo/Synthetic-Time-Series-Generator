#include <iostream>
#include <string>
#include <unordered_map>
#include "augment.h"

int main() {
    std::unordered_map<std::string, unsigned int> mp 
        {{"Daily", 4227}, 
        {"Hourly", 414},
        {"Monthly", 48000},
        {"Quarterly", 24000},
        {"Weekly", 359},
        {"Yearly", 23000}};
    std::string dir_path, csv_path, first_letter;

    // offset used to determine when to update progress bar
    int offset_mod = static_cast<int>(100000 / 10);
    int offset_counter {0};
    int offset_i {0};
    // print initial progress bar
    std::cout << "[";
    for (auto i = 0; i < 10; i++) {
        std::cout << " ";
    }
    std::cout << "]\r";

    for (const auto& ele : mp) {
        dir_path = "./Datasets/" + ele.first + "/Train/";
        first_letter = ele.first.substr(0, 1);
        for (auto i = 1; i < ele.second + 1; i++) {
            // print progress bar
            if ((++offset_i - 1) % offset_mod == 0) {
                offset_counter++;

                std::cout << "[";
                for (auto i = 0; i < offset_counter; i++) {
                    std::cout << "X";
                }
                for (auto i = 0; i < 10 - offset_counter; i++) {
                    std::cout << " ";
                }
                std::cout << "]\r";
            }
            // augmenting data
            csv_path = dir_path + first_letter + std::to_string(i) + ".csv";
            aug::augment_data(csv_path);
        }
    }

    return 0;
}
