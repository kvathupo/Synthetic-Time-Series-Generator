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
#include "ARPoly.h"
#include "DatasetPoly.h"
#include "GaussSeq.h"
#include "ZeroSeq.h"
#include "utils.h"
using utils::my_float;
using boost::random::uniform_real_distribution;


/*
 *  Helper functions
 *
 *  All "noise setters" require that the target sequence be defined.
 */
void DatasetPoly::noise_zero() {
    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<ZeroSeq>());
    }
    feats[utils::SALIENT_IND] = std::make_unique<ARPoly>(this->target);
}
void DatasetPoly::noise_one() {
    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<GaussSeq>());
    }
    feats[utils::SALIENT_IND] = std::make_unique<ARPoly>(this->target);
}
void DatasetPoly::noise_two() {
    uniform_real_distribution<my_float> u_mean(-10, 10);
    uniform_real_distribution<my_float> u_std(0.1, 5);

    for (auto i = 0; i < utils::FEAT_COUNT; i++) {
        feats.push_back(std::make_unique<GaussSeq>(u_mean(gen), u_std(gen)));
    }
    feats[utils::SALIENT_IND] = std::make_unique<ARPoly>(this->target);
}
void DatasetPoly::noise_three() {
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
    feats[utils::SALIENT_IND] = std::make_unique<ARPoly>(this->target);
}
void DatasetPoly::noise_four() {
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
    feats[utils::SALIENT_IND] = std::make_unique<ARPoly>(this->target);
}


/*
 *  Constructors and destructors
 */
DatasetPoly::DatasetPoly(std::string file_name, ARPoly target_seq) {
    target = target_seq;
    fname = file_name.append(".csv");
}

DatasetPoly::DatasetPoly(std::string file_name, ARPoly target_seq, unsigned char type) {
    target = target_seq;
    fname = file_name.append(".csv");
    noise_type = type;
    set_noise(type);
}
