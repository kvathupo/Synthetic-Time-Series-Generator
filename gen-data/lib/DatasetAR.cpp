#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <memory>
#include <map>
#include <cassert>
#include <fstream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp> 
#include "DatasetAR.h"
#include "GaussSeq.h"
#include "ZeroSeq.h"
#include "utils.h"
using utils::my_float;
using boost::random::uniform_real_distribution;


/*
 *  Member variables
 */
boost::random::mt19937 DatasetAR::gen {};


/*
 *  Helper functions
 *
 *  All "noise setters" require the target sequence be defined.
 */
void DatasetAR::noise_zero() {
    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<ZeroSeq>());
    }
    feats[utils::SALIENT_IND] = std::make_unique<ARSeq>(this->target);
}
void DatasetAR::noise_one() {
    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<GaussSeq>());
    }
    feats[utils::SALIENT_IND] = std::make_unique<ARSeq>(this->target);
}
void DatasetAR::noise_two() {
    uniform_real_distribution<my_float> u_mean(-10, 10);
    uniform_real_distribution<my_float> u_std(0.1, 5);

    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<GaussSeq>(u_mean(gen), u_std(gen)));
    }
    feats[utils::SALIENT_IND] = std::make_unique<ARSeq>(this->target);
}
void DatasetAR::noise_three() {
    uniform_real_distribution<my_float> u_const(0, 1);
    uniform_real_distribution<my_float> u_coeff(-0.9, 0.9);
    uniform_real_distribution<my_float> u_seed(-1, 1);
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
    feats[utils::SALIENT_IND] = std::make_unique<ARSeq>(this->target);
}
void DatasetAR::noise_four() {
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
    feats[utils::SALIENT_IND] = std::make_unique<ARSeq>(this->target);
}


/*
 *  Constructors and destructors
 */
DatasetAR::DatasetAR(std::string file_name, ARSeq target_seq):
    fname{file_name.append(".csv")},
    target{target_seq}
    {};

DatasetAR::DatasetAR(std::string file_name, ARSeq target_seq, unsigned char type):
    fname{file_name.append(".csv")},
    noise_type{type},
    target{target_seq} {
    set_noise(type);
}


/*
 *  Member functions
 */
void DatasetAR::set_noise(unsigned char type) {
    this->noise_type = type;

    switch (type) {
        case 0: this->noise_zero();
                break;
        case 1: this->noise_one();
                break;
        case 2: this->noise_two();
                break;
        case 3: this->noise_three();
                break;
        case 4: this->noise_four();
                break;
    }
    this->prev_targ_val = feats[utils::SALIENT_IND]->next();
}
std::array<std::array<my_float, utils::FEAT_COUNT + 1>, utils::TIME_STEP>
    DatasetAR::generate_normalized_dat() {
    namespace mp = boost::multiprecision;
    constexpr int T = utils::TIME_STEP;
    constexpr int F = utils::FEAT_COUNT;
    // observe storage[feat][time] indexing
    std::array<std::array<my_float, T + 1>, F> storage {};  
    std::array<my_float, T + 1> targ_storage {};            // storage for target

    /*
     *  Prepare progress bar
     */

    // offset used to determine when to update progress bar
    int offset_mod = static_cast<int>(F / 10);
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
    // If noise type 3 or 4, then there is one previous value as a ARSeq.
    // Otherwise, simply invoke next()
    if (this->noise_type == 3 || this->noise_type == 4) {
        for (auto f = 0; f < F; f++) {
            if (f == utils::SALIENT_IND) 
                targ_storage[0] = this->prev_targ_val;
            else 
                storage[f][0] = dynamic_cast<ARSeq*>(feats[f].get())->get_prev_val()[0];
        }
    } else {
        for (auto f = 0; f < F; f++) {
            if (f == utils::SALIENT_IND) 
                targ_storage[0] = this->prev_targ_val;
            else 
                storage[f][0] = feats[f]->next();
        }
    }

    // Store current values (those non-negative)
    for (auto f = 0; f < F; f++) {
        // print progress bar
        if ((f - 1) % offset_mod == 0) {
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
        for (int t = 1; t < T + 1; t++) {
            if (f != utils::SALIENT_IND) 
                storage[f][t] = feats[f]->next();
            else {
                // target column
                this->prev_targ_val = feats[utils::SALIENT_IND]->next();
                targ_storage[t] = this->prev_targ_val;
            }
        }
    }

    /*
     *  Normalize array values according to utils::NORM_VAL via min-max norm
     */
    my_float feat_min {0};
    my_float feat_max {0};
    // observe normalized_feats[time][feat] indexing
    std::array<std::array<my_float, F + 1>, T> normalized_feats {};

    // set normalized non-targ vals
    for (auto f = 0; f < F; f++) {
        if (f != utils::SALIENT_IND) {
            // if we have zero values, no need to rescale
            if (this->noise_type == 0) {
                for (auto t = 0; t < T; t++) {
                    normalized_feats[t][f] = storage[f][t];
                }
            } else {
                feat_min = *std::min_element(storage[f].begin(), storage[f].end());
                feat_max = *std::max_element(storage[f].begin(), storage[f].end());
                
                for (auto t = 0; t < T; t++) {
                    if (feat_max - feat_min == 0) 
                        normalized_feats[t][f] = (utils::NORM_VAL * 2 * (storage[f][t] - feat_min)) - 
                            utils::NORM_VAL;
                    else
                        normalized_feats[t][f] = (utils::NORM_VAL * 2 * ((storage[f][t] - feat_min) / 
                            (feat_max - feat_min))) - utils::NORM_VAL;
                }
            }
        } else {
            feat_min = *std::min_element(targ_storage.begin(), targ_storage.end());
            feat_max = *std::max_element(targ_storage.begin(), targ_storage.end());

            for (auto t = 0; t < T; t++) {
                if (feat_max - feat_min == 0) {
                    normalized_feats[t][utils::SALIENT_IND] = (utils::NORM_VAL * 2 * (targ_storage[t] - feat_min)) - 
                        utils::NORM_VAL;
                    normalized_feats[t][F] = (utils::NORM_VAL * 2 * (targ_storage[t + 1] - feat_min)) - 
                        utils::NORM_VAL;
                } else {
                    normalized_feats[t][utils::SALIENT_IND] = (utils::NORM_VAL * 2 * ((targ_storage[t] - feat_min) / 
                        (feat_max - feat_min))) - utils::NORM_VAL;
                    normalized_feats[t][F] = (utils::NORM_VAL * 2 * ((targ_storage[t + 1] - feat_min) / 
                        (feat_max - feat_min))) - utils::NORM_VAL;
                }
            }
        }
    }

    return normalized_feats;
} 

void DatasetAR::write_csv() {
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

    // write values to csv
    for (auto t = 0; t < T; t++) {
        for (auto f = 0; f < F + 2; f++) {
            // time column
            if (f == 0)
                synth_data << t << ",";
            // target column
            else if (f == utils::FEAT_COUNT + 1)
                synth_data << storage[t][f - 1] << "\n";
            // data column
            else 
                synth_data << storage[t][f - 1] << ",";
        }
    }
    std::cout << "\nFinished writing " << this->fname << "!\n";
    synth_data.close();
}
