#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "utils.h"
#include "Seq.h"
#include "GaussSeq.h"

using utils::my_float;
namespace fs = std::filesystem;

namespace aug {
/*
 *  Augment csv by writing to folder and deleting the original.
 *
 *  :param csv_path: Path to the training csv with one feature and one target
 *  :param dir_expand: If true, stores augmented data in directory with 
 *  the csv file's name.
 *  :param prefix: The prefix for the augmented data, of which `count` many
 *  are generated
 *  :param count: Number of augmented datasets to create
 *  :param noise: Additive noise sequence
 *
 *  :throws:
 *      * Invalid csv_path
 *      * Directory already exists with expand
 */
void augment_data(std::string csv_path,
    bool dir_expand = true, std::string prefix = "dat", 
    unsigned int count = 10, 
    std::unique_ptr<Seq> noise = std::make_unique<GaussSeq>()) {
    if (!fs::exists(csv_path)) 
        throw std::runtime_error(csv_path + " does not exist!\n");

    std::ifstream strm(csv_path);
    std::string dir_path;
    
    // Create directory if needed
    if (dir_expand) {
        dir_path = csv_path.substr(0, csv_path.size() - 4);
        dir_path += '/';
        fs::create_directory(dir_path);
    } else {
        dir_path = csv_path.substr(0, csv_path.find_last_of('/') + 1);
    }

    /*
     *  Record contents
     */
    unsigned int n_lines = std::count(std::istreambuf_iterator<char>(strm),
        std::istreambuf_iterator<char>(), '\n');
    std::vector<my_float> v(n_lines, 0);
    strm.seekg(0);

    char comma;
    float num, num_2;
    std::string header;
    std::getline(strm, header);             // skip header
    strm >> num >> comma >> num >> comma >> num_2;          // read first two
    v[0] = num;
    v[1] = num_2;

    unsigned int idx = 2;
    while (strm.good()) {
        strm >> num >> comma >> num >> comma >> num;            // read last num 
        if (strm.eof())
            break;
        v[idx++] = num;
    }
    strm.close();
    
    /*
     *  Writing new data
     */
    // Writing meta-data
    my_float min = *std::min_element(v.begin(), v.end());
    my_float max = *std::max_element(v.begin(), v.end());
    std::ofstream out_s(dir_path + "meta.csv");
    out_s << "Min,Max,Len\n";
    out_s << min << ',' << max << ',' << n_lines;
    out_s.close();

    // Writing augmented data where the first index is the original data scaled
    std::vector<my_float> aug_v (n_lines, 0);
    for (decltype(count) i = 1; i < count + 1; i++) {
        aug_v = v;
        if (i != 1) {
            for (std::size_t j = 0; j < aug_v.size(); j++) {
                aug_v[j] += noise->next();
            }
        }
        min = *std::min_element(aug_v.begin(), aug_v.end());
        max = *std::max_element(aug_v.begin(), aug_v.end());

        for (std::size_t j = 0; j < aug_v.size(); j++) {
            aug_v[j] = (((aug_v[j] - min) / (max - min)) * 2) - 1;            // min-max scale to [-1, 1]
        }

        // Writing actual data
        out_s.open(dir_path + prefix + std::to_string(i) + ".csv");
        out_s << std::setprecision(25);
        out_s << "Time,Feature_1,Target\n";
        for (std::size_t j = 0; j < aug_v.size() - 1; j++) {
            if (j == 0) 
                out_s << j << ',' << aug_v[0] << ',' << aug_v[1] << '\n';
            else
                out_s << j << ',' << aug_v[j] << ',' << aug_v[j + 1] << '\n';
        }
        out_s.close();
    }

    // Delete original csv
    fs::remove(csv_path);
}
}
