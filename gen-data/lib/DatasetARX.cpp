#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <memory>
#include <map>
#include <cassert>
#include <fstream>
#include "DatasetARX.h"
#include "GaussSeq.h"
#include "ZeroSeq.h"
#include "utils.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp> 
using utils::my_float;
using boost::random::uniform_real_distribution;


/*
 *  Member variables
 */
boost::random::mt19937 DatasetARX::gen {};      // static generator

/*
 *  Helper member functions
 */

// Seed previous values from uniform distribution
void DatasetARX::seed_features() {
    uniform_real_distribution<my_float> u_seed(-1, 1);

    feat_5[0] = u_seed(gen);
    for (auto i = 0; i < 3; i++) {
        feat_10[i] = u_seed(gen);
    }
    for (auto i = 0; i < 5; i++) {
        feat_20[i] = u_seed(gen);
    }
}
void DatasetARX::noise_one() {
    this->seed_features();
    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<GaussSeq>());
    }
}
void DatasetARX::noise_two() {
    this->seed_features();

    uniform_real_distribution<my_float> u_mean(-10, 10);
    uniform_real_distribution<my_float> u_std(0.1, 5);

    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<GaussSeq>(u_mean(gen), u_std(gen)));
    }
}
void DatasetARX::noise_three() {
    this->seed_features();

    uniform_real_distribution<my_float> u_const(0, 1);
    uniform_real_distribution<my_float> u_coeff(-0.9, 0.9);
    uniform_real_distribution<my_float> u_seed(0, 1);
    std::vector<my_float> seed_vect {u_seed(gen),};
    std::map<int, my_float> coeff_map {
        {1, u_coeff(gen)},
    };

    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        // prep seq backing
        coeff_map[1] = u_coeff(gen);
        seed_vect[0] = u_seed(gen);

        ARSeq in_seq(coeff_map, u_const(gen));
        in_seq.seed_prev_vals(seed_vect);

        feats.push_back(std::make_unique<ARSeq>(in_seq));
    }
}
void DatasetARX::noise_four() {
    this->seed_features();

    uniform_real_distribution<my_float> u_const(-1000000, -999999);
    uniform_real_distribution<my_float> u_coeff(1.1, 2);
    uniform_real_distribution<my_float> u_seed(0, 0.0000001);
    std::vector<my_float> seed_vect {u_seed(gen),};
    std::map<int, my_float> coeff_map {
        {1, u_coeff(gen)},
    };

    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        // prep seq backing
        coeff_map[1] = u_coeff(gen);
        seed_vect[0] = u_seed(gen);

        ARSeq in_seq(coeff_map, u_const(gen));
        in_seq.seed_prev_vals(seed_vect);

        feats.push_back(std::make_unique<ARSeq>(in_seq));
    }
}

/*
 *  Constructors and destructors
 */
DatasetARX::DatasetARX(std::string file_name):
    fname{file_name.append(".csv")}
    {};

DatasetARX::DatasetARX(std::string file_name,  unsigned char type):
    fname{file_name.append(".csv")},
    noise_type{type} {
    set_noise(type);
}

/*
 *  Member functions
 */
void DatasetARX::set_noise(unsigned char type) {
    this->noise_type = type;

    switch (type) {
        case 1: this->noise_one();
                break;
        case 2: this->noise_two();
                break;
        case 3: this->noise_three();
                break;
        case 4: this->noise_four();
                break;
    }
}
std::array<std::array<my_float, utils::FEAT_COUNT + 1>, utils::TIME_STEP>
    DatasetARX::generate_normalized_dat() {
    namespace mp = boost::multiprecision;
    constexpr int T = utils::TIME_STEP;
    constexpr int F = utils::FEAT_COUNT;
    // observe storage[feat][time] indexing
    std::array<std::array<my_float, T + 1>, F + 1> storage {};

    /*
     *  Prepare progress bar
     */
    // offset used to determine when to update progress bar
    int offset_mod = static_cast<int>(T / 10);
    int offset_counter {0};
    // print initial progress bar
    std::cout << "[";
    for (auto i = 0; i < 10; i++) {
        std::cout << " ";
    }
    std::cout << "]\r";


    /*
     *  Store non-normalized values
     */

    // Store time-delayed values
    // If of noise types 3 or 4, then there is one previous value as a ARSeq.
    // Otherwise, simply invoke next()
    if (this->noise_type == 3 || this->noise_type == 4) {
        for (auto f = 0; f < F + 1; f++) {
            if (f == F) 
                storage[f][0] = 0.1*feat_5[0] + 0.25*feat_10[2] + 0.5*feat_20[4] + 
                    error_term.next();
            else
                storage[f][0] = dynamic_cast<ARSeq*>(feats[f].get())->get_prev_val()[0];
        }
    } else {
        for (auto f = 0; f < F + 1; f++) {
            if (f == F) 
                storage[f][0] = 0.1*feat_5[0] + 0.25*feat_10[2] + 0.5*feat_20[4] + 
                    error_term.next();
            else 
                storage[f][0] = feats[f]->next();
        }
    }

    // Store current values (those non-negative)
    my_float temp_feat_5 {0};
    my_float temp_feat_10 {0};
    my_float temp_feat_20 {0};

    for (auto t = 1; t < T + 1; t++) {
        // print progress bar
        if ((t - 1) % offset_mod == 0) {
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

        // write and record sequences
        for (auto f = 0; f < F + 1; f++) {
            // target column
            if (f == F) {
                storage[f][t] = 0.1*feat_5[0] + 0.25*feat_10[2] + 0.5*feat_20[4] + 
                    error_term.next();

                // update past values
                utils::shift_vector(this->feat_5);
                utils::shift_vector(this->feat_10);
                utils::shift_vector(this->feat_20);

                feat_5[0] = temp_feat_5;
                feat_10[0] = temp_feat_10;
                feat_20[0] = temp_feat_20;
            } else if (f == 5) {
                temp_feat_5 = feats[f]->next();
                storage[f][t] = temp_feat_5;
            } else if (f == 10) {
                temp_feat_10 = feats[f]->next();
                storage[f][t] = temp_feat_10;
            } else if (f == 20) {
                temp_feat_20 = feats[f]->next();
                storage[f][t] = temp_feat_20;
            } else {
                storage[f][t] = feats[f]->next();
            }
        }
    }

    /*
     *  Normalize array values according to utils::NORM_VAL
     */
    my_float feat_min {0};
    my_float feat_max {0};
    // observe normalized_feats[time][feat] indexing
    std::array<std::array<my_float, F + 1>, T> normalized_feats {};

    // no need to check for zero values since we cannot use those with ARX
    for (auto f = 0; f < F + 1; f++) {
        feat_min = *std::min_element(storage[f].begin(), storage[f].end());
        feat_max = *std::max_element(storage[f].begin(), storage[f].end());

        for (auto t = 0; t < T; t++) {
            if (feat_max - feat_min == 0) 
                normalized_feats[t][f] = (utils::NORM_VAL * 2 * (storage[f][t + 1] - feat_min)) - 
                    utils::NORM_VAL;
            else
                normalized_feats[t][f] = (utils::NORM_VAL * 2 * ((storage[f][t + 1] - feat_min) / 
                    (feat_max - feat_min))) - utils::NORM_VAL;
        }
    }

    return normalized_feats;
} 

void DatasetARX::write_csv() {
    // was the noise value assigned?
    assert(this->noise_type != 10);


    // storage for normalize values
    constexpr int T = utils::TIME_STEP;
    constexpr int F = utils::FEAT_COUNT;
    std::array<std::array<my_float, F + 1>, T> storage = generate_normalized_dat();

    // initialize csv
    std::ofstream synth_data {this->fname};
    synth_data << std::setprecision(25);
    
    // prepare labels
    for (auto i = 0; i < utils::FEAT_COUNT + 2; i++) {
        if (i == 0)
            synth_data << "Time,";
        else if (i == utils::FEAT_COUNT + 1)
            synth_data << "Target\n";
        else 
            synth_data << "Feature_" << i << ",";
    }

    // write values
    for (auto t = 0; t < T; t++) {
        for (auto f = 0; f < F + 2; f++) {
            // time column
            if (f == 0)
                synth_data << t << ",";
            // target column
            else if (f == utils::FEAT_COUNT + 1) {
                synth_data << storage[t][f - 1] << "\n";
            } else {
                synth_data << storage[t][f - 1] << ",";
            }
        }
    }
    std::cout << "\nFinished writing " << this->fname << "!\n";
    synth_data.close();
}
